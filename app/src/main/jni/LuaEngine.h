//
// Created by Administrator on 2019/7/18.
//

#ifndef ANDROIDLUA_LUAENGINE_H
#define ANDROIDLUA_LUAENGINE_H

#include <cstring>
#include <string>
#include "lua/lua.hpp"
#include "android/log.h"

#include "shell.h"

#define LOG_TAG "LuaEngine"

class LuaEngine {
public:
    LuaEngine();

    virtual ~LuaEngine();

    lua_State *getScriptContext();

    bool startScript(const char *luaString);

    bool isScriptRunning();

    bool stopScript();

private:
    lua_State *mScriptContext;
    bool scriptRunning;

    bool registerCFunction();
};

void quitLuaThread(lua_State *L);
void quitLuaThreadHooker(lua_State* L, lua_Debug* ar);

#endif //ANDROIDLUA_LUAENGINE_H
