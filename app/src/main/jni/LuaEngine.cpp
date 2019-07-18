//
// Created by Administrator on 2019/7/18.
//

#include "LuaEngine.h"
#include "utils/Log.h"

LuaEngine::LuaEngine() {
    mScriptContext = luaL_newstate();
    scriptRunning = false;
}

LuaEngine::~LuaEngine() {
    mScriptContext = nullptr;
}

bool LuaEngine::startScript(const char *luaString, const char *functionName) {
    luaL_openlibs(mScriptContext);
    this->registerCFunction();
    if (this->loadBuff(luaString)) {
        return this->runLuaFunction(functionName);
    } else {
        return false;
    }
}

bool LuaEngine::stopScript() {
    quitLuaThread(mScriptContext);
    return true;
}

bool LuaEngine::isScriptRunning() {
    return scriptRunning;
}

bool LuaEngine::registerCFunction() {
    int len = sizeof(mCFunctions) / sizeof(CFunction);
    for (int i = 0; i < len; i++) {
        lua_register(mScriptContext, mCFunctions[i].name, mCFunctions[i].func);
    }
    return true;
}

lua_State *LuaEngine::getScriptContext() {
    return mScriptContext;
}

bool LuaEngine::loadBuff(const char *buff) {
    // 读取buff
    if (LUA_OK != luaL_loadbuffer(mScriptContext, buff, strlen(buff), NULL)) {
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
