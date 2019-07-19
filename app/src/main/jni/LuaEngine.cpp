//
// Created by Administrator on 2019/7/18.
//

#include "LuaEngine.h"
#include "utils/Log.h"
#include "JniManager.h"

LuaEngine::LuaEngine() {
    mScriptContext = luaL_newstate();
    scriptRunning = false;
}

LuaEngine::~LuaEngine() {
    if (isScriptRunning()) {
        stopScript();
    }
    mScriptContext = nullptr;
}

bool LuaEngine::startScript(jstring jBuff, const char *functionName) {
    scriptRunning = true;
    luaL_openlibs(mScriptContext);
    this->registerCFunction();
    if (this->loadBuff(jBuff)) {
        bool success = this->runLuaFunction(functionName);
        scriptRunning = false;
        return success;
    } else {
        scriptRunning = false;
        return false;
    }
}

bool LuaEngine::stopScript() {
    if (scriptRunning) {
        quitLuaThread(mScriptContext);
        scriptRunning = false;
        return true;
    } else {
        Log_d(LOG_TAG, "script is Not running");
        return false;
    }
}

bool LuaEngine::registerCFunction() {
    int len = sizeof(mCFunctions) / sizeof(CFunction);
    for (int i = 0; i < len; i++) {
        lua_register(mScriptContext, mCFunctions[i].name, mCFunctions[i].func);
    }
    return true;
}

bool LuaEngine::loadBuff(jstring jBuff) {
    // 读取buff
    JNIEnv *env;
    JniManager::getInstance()->getJvm()->GetEnv((void **) &env, JNI_VERSION_1_6);
    const char *cBuff = env->GetStringUTFChars(jBuff, nullptr);
    if (LUA_OK != luaL_loadbuffer(mScriptContext, cBuff, strlen(cBuff), NULL)) {
        const char *szError = luaL_checkstring(mScriptContext, -1);
        Log_e(LOG_TAG, "%s", szError);
        return false;
    }
    // 加载buff到内存
    if (LUA_OK != lua_pcall(mScriptContext, 0, LUA_MULTRET, 0)) {
        const char *szError = luaL_checkstring(mScriptContext, -1);
        Log_e(LOG_TAG, "%s", szError);
        return false;
    }
    env->ReleaseStringUTFChars(jBuff, cBuff);
    env->DeleteGlobalRef(jBuff);
    return true;
}

bool LuaEngine::runLuaFunction(const char *functionName) {
    // 获取errorFunc
    lua_getglobal(mScriptContext, "__TRACKBACK__");
    if (lua_type(mScriptContext, -1) != LUA_TFUNCTION) {
        return false;
    }
    int errfunc = lua_gettop(mScriptContext);

    // 获取指定的方法
    lua_getglobal(mScriptContext, functionName);
    if (lua_type(mScriptContext, -1) != LUA_TFUNCTION) {
        return false;
    }

    // 跑指定的方法
    return LUA_OK == lua_pcall(mScriptContext, 0, 0, errfunc);
}

void quitLuaThread(lua_State *L) {
    int mask = LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE | LUA_MASKCOUNT;
    lua_sethook(L, &quitLuaThreadHooker, mask, 0);
}

void quitLuaThreadHooker(lua_State *L, lua_Debug *ar) {
    luaL_error(L, "quit Lua");
}
