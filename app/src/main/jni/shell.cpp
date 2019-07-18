
#include <zconf.h>
#include "lua/lua.h"
#include "android/log.h"

static int CPrintMsg(lua_State *L) {
    const char *msg = lua_tostring(L, 1);
    __android_log_print(ANDROID_LOG_DEBUG, "Shell", "CPrintMsg: %s", msg);
    return 0;
}

static int sleepMilliseconds(lua_State *L) {
    int milliseconds = static_cast<int>(lua_tointeger(L, 1));
    usleep(static_cast<useconds_t>(milliseconds * 1000));
    return 0;
}