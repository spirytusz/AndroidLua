
#include "luabridge.h"

bool startScript(JNIEnv *env, jobject obj, jstring luaStr) {
    if(mLuaTask) {
        Log_d(LOG_TAG, "script is running!");
        return false;
    }

    const char *luaString = env->GetStringUTFChars(luaStr, nullptr);
    mLuaTask = new LuaTask(luaString);
    mLuaTask->startWork();
    env->ReleaseStringUTFChars(luaStr, luaString);
    return true;
}

bool stopScript(JNIEnv *env, jobject obj) {
    if(mLuaTask) {
        mLuaTask->stopWork();
        delete mLuaTask;
        return true;
    } else {
        return false;
    }
}

bool isScriptRunning(JNIEnv *env, jobject obj) {
    if (mLuaTask) {
        return mLuaTask->isRunning();
    } else {
        return false;
    }
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