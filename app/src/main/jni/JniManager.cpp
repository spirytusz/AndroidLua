//
// Created by Administrator on 2019/7/19.
//

#include "JniManager.h"

JniManager *JniManager::instance = nullptr;

JniManager *JniManager::getInstance() {
    if (!instance) {
        instance = new JniManager();
    }
    return instance;
}

void JniManager::initJniManager(JavaVM *jvm, JNIEnv *env) {
    mPJvm = jvm;
    inRefJavaClass(env);
}

void JniManager::inRefJavaClass(JNIEnv *env) {
    for (char *className : classes) {
        jclass g_jClass = env->FindClass(className);
        if (!g_jClass) {
            Log_d(LOG_TAG, "Class %s Not Found", className);
            continue;
        }
        classMapper[className] = (jclass) env->NewGlobalRef(g_jClass);
    }
}

void JniManager::getMethodId(char* className, char* methodName, char* sig, jclass &clazz, jmethodID &methodId) {
    clazz = classMapper[className];
    JNIEnv* env;
    mPJvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    methodId = env->GetStaticMethodID(clazz, methodName, sig);
}

void JniManager::attachCurrentThread(JNIEnv *env) {
    JavaVM *jvm = JniManager::getInstance()->getJvm();
    int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (JNI_OK == status) {
        // 已经attach过了
        return;
    }
    JavaVMAttachArgs args{JNI_VERSION_1_6, nullptr, nullptr};
    jvm->AttachCurrentThread(&env, &args);
}

void JniManager::detachCurrentThread() {
    JavaVM *jvm = JniManager::getInstance()->getJvm();
    if (jvm) {
        jvm->DetachCurrentThread();
    }
}
