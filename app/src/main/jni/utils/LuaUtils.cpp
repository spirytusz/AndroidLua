//
// Created by Administrator on 2019/7/24.
//

#include "LuaUtils.h"

void dumpStack(lua_State *L) {
    int i = lua_gettop(L);
    // 获取栈的长度
    Log_d(LUA_UTILS_TAG, "-------------------  Stack Dump -------------------");
    while (i) {
        int t = lua_type(L, i);
        // 获取栈中索引为i的元素的类型
        switch (t) {
            case LUA_TSTRING:
                Log_d(LUA_UTILS_TAG, "%d:`%s'", i, lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                Log_d(LUA_UTILS_TAG, "%d: %s", i, lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                Log_d(LUA_UTILS_TAG, "%d: %g", i, lua_tonumber(L, i));
                break;
            default:
                Log_d(LUA_UTILS_TAG, "%d: %s", i, lua_typename(L, t));
                break;
        }
        i--;
    }
    Log_d(LUA_UTILS_TAG, "--------------- Stack Dump Finished ---------------");
}

