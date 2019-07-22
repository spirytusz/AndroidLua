//
// Created by Administrator on 2019/7/18.
//

#ifndef ANDROIDLUA_SHELL_H
#define ANDROIDLUA_SHELL_H

#include <zconf.h>
#include "lua/lua.hpp"

#include "utils/Log.h"
#include "JniManager.h"
#include "LuaEngine.h"

typedef struct {
    const char *name;
    lua_CFunction func;
} CFunction;

int CPrintMsg(lua_State *L);

int sleepMilliseconds(lua_State *L);

int sleepSeconds(lua_State *L);

int getString(lua_State *L);

int getData(lua_State *L);

static CFunction mCFunctions[] = {
        {"CPrintMsg",         CPrintMsg},
        {"sleepMilliseconds", sleepMilliseconds},
        {"sleepSeconds",      sleepSeconds},
        {"getString",         getString},
        {"getData",           getData},
};

#endif //ANDROIDLUA_SHELL_H
