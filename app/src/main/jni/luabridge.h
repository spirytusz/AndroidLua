//
// Created by Administrator on 2019/7/16.
//

#ifndef ANDROIDLUABRIDGE_LUABRIDGE_H
#define ANDROIDLUABRIDGE_LUABRIDGE_H

#include <jni.h>
#include <string>
#include "android/log.h"

#include "LuaTask.h"

LuaTask *mLuaTask;

bool startScript(JNIEnv *env, jobject obj, jstring luaStr);

bool stopScript(JNIEnv *env, jobject obj);

bool isScriptRunning(JNIEnv *env, jobject obj);

static JNINativeMethod nativeMethods[] = {
        {"startScript",     "(Ljava/lang/String;)Z", (void *) startScript},
        {"isScriptRunning", "()Z",                   (void *) isScriptRunning},
        {"stopScript",      "()Z",                   (void *) stopScript},
};

static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *nativeMethods,
                                 int methodsNum) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, nativeMethods, methodsNum) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

#endif //ANDROIDLUABRIDGE_LUABRIDGE_H
