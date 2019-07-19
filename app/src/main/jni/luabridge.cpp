
#include "luabridge.h"
#include "JniManager.h"

bool startScript(JNIEnv *env, jobject obj, jstring luaStr) {
    if(mLuaTask) {
        Log_d(LOG_TAG, "script is running!");
        return false;
    }
    jstring g_jBuff = (jstring)env->NewGlobalRef(luaStr);
    mLuaTask = new LuaTask(g_jBuff);
    mLuaTask->startWork();
    return true;
}

bool stopScript(JNIEnv *env, jobject obj) {
    if(mLuaTask) {
        Log_d(LOG_TAG, "running!!");
        mLuaTask->stopWork();
        delete mLuaTask;
        mLuaTask = nullptr;
        return true;
    } else {
        Log_d(LOG_TAG, "NOT running!!");
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
    JniManager::getInstance()->initJniManager(vm, env);
    if (!registerNativeMethods(env, "com/zspirytus/androidlua/MainActivity", nativeMethods,
                               sizeof(nativeMethods) / sizeof(nativeMethods[0]))) {
        return -1;
    }
    return JNI_VERSION_1_6;
}