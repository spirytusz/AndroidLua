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

bool LuaEngine::startScript(const char *luaString) {
    luaL_openlibs(mScriptContext);
    this->registerCFunction();
    // 读取buff
    if (LUA_OK != luaL_loadbuffer(mScriptContext, luaString, strlen(luaString), NULL)) {
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

    // 获取errorFunc
    lua_getglobal(mScriptContext, "__TRACKBACK__");
    if (lua_type(mScriptContext, -1) != LUA_TFUNCTION) {
        return false;
    }
    int errfunc = lua_gettop(mScriptContext);

    // 获取main方法
    lua_getglobal(mScriptContext, "main");
    if (lua_type(mScriptContext, -1) != LUA_TFUNCTION) {
        return false;
    }

    // 跑main方法
    return LUA_OK == lua_pcall(mScriptContext, 0, 0, errfunc);
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

void quitLuaThread(lua_State *L) {
    int mask = LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE | LUA_MASKCOUNT;
    lua_sethook(L, &quitLuaThreadHooker, mask, 0);
}

void quitLuaThreadHooker(lua_State* L, lua_Debug* ar) {
    luaL_error(L, "quit Lua");
}
