
#include "shell.h"

int CPrintMsg(lua_State *L) {
    const char *msg = lua_tostring(L, 1);
    Log_d("Shell", "CPrintMsg: %s", msg);
    return 0;
}

int sleepMilliseconds(lua_State *L) {
    int milliseconds = static_cast<int>(lua_tointeger(L, 1));
    usleep(static_cast<useconds_t>(milliseconds * 1000));
    return 0;
}

int sleepSeconds(lua_State *L) {
    int second = static_cast<int>(lua_tointeger(L, 1));
    for(int i = 0;i<second;i++) {
        sleep(1);
    }
    return 0;
}