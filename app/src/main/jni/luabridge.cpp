#include <jni.h>
#include <string>
#include "luabridge.h"
#include "lua/lua.hpp"
#include "lua/lapi.h"
#include "android/log.h"
#include "shell.cpp"
#include "lua/lstate.h"

static bool g_isRunning = false;
lua_State *mLuaContext = NULL;

void registerLuaFunction() {
    lua_register(mLuaContext, "CPrintMsg", CPrintMsg);
    lua_register(mLuaContext, "sleepMilliseconds", sleepMilliseconds);
}

bool runScript(lua_State *L, const char* luaString) {
    // 读取buff
    if (LUA_OK != luaL_loadbuffer(L, luaString, strlen(luaString), NULL)) {
        const char *szError = luaL_checkstring(L, -1);
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", szError);
        return false;
    }
    // 加载buff到内存
    if (LUA_OK != lua_pcall(L, 0, LUA_MULTRET, 0)) {
        const char *szError = luaL_checkstring(L, -1);
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", szError);
        return false;
    }

    // 获取errorFunc
    lua_getglobal(L, "__TRACKBACK__");
    if (lua_type(L, -1) != LUA_TFUNCTION) {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", "errorMsg: 1");
        return false;
    }
    int errfunc = lua_gettop(L);

    // 获取main方法
    lua_getglobal(L, "main");
    if (lua_type(L, -1) != LUA_TFUNCTION) {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s","errorMsg: 2");
        return false;
    }

    // 跑main方法
    if (LUA_OK != lua_pcall(L, 0, 0, errfunc)) {
        const char *szError = lua_tostring(L, -1);
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "errorMsg: %s", szError);
        return false;
    }
    return true;
}

bool startScript(JNIEnv *env, jobject obj, jstring luaStr) {
    const char* luaString = env->GetStringUTFChars(luaStr, nullptr);
    mLuaContext = luaL_newstate();
    luaL_openlibs(mLuaContext);
    registerLuaFunction();
    g_isRunning = true;
    return runScript(mLuaContext, luaString);
}

bool stopScript(JNIEnv *env, jobject obj) {
    g_isRunning = false;
    return true;
}

bool isScriptRunning(JNIEnv *env, jobject obj) {
    return g_isRunning;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);
    if (!registerNativeMethods(env, "com/zspirytus/androidlua/MainActivity", nativeMethods,
                               sizeof(nativeMethods) / sizeof(nativeMethods[0]))) {
        return -1;
    }
    return JNI_VERSION_1_6;
}