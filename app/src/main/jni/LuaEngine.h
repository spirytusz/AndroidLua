//
// Created by Administrator on 2019/7/18.
//

#ifndef ANDROIDLUA_LUAENGINE_H
#define ANDROIDLUA_LUAENGINE_H

#include <cstring>
#include <string>
#include <jni.h>
#include "lua/lua.hpp"

#include "utils/Log.h"
#include "JniManager.h"

#include "shell.h"

#define LOG_TAG "LuaEngine"

class LuaEngine {
public:
    LuaEngine();

    virtual ~LuaEngine();

    lua_State *getScriptContext() {
        return mScriptContext;
    }

    bool startScript(jstring jBuff, const char *functionName);

    bool isScriptRunning() {
        return scriptRunning;
    }

    bool stopScript();

private:
    lua_State *mScriptContext;
    bool scriptRunning;

    bool registerCFunction();

    bool loadBuff(jstring jBuff);

    bool runLuaFunction(const char *functionName);
};

void quitLuaThread(lua_State *L);

void quitLuaThreadHooker(lua_State *L, lua_Debug *ar);

#endif //ANDROIDLUA_LUAENGINE_H
