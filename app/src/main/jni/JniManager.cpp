//
// Created by Administrator on 2019/7/19.
//

#include "JniManager.h"

JniManager* JniManager::instance = nullptr;

JniManager *JniManager::getInstance() {
    if (!instance) {
        instance = new JniManager();
    }
    return instance;
}

void JniManager::initJniManager(JavaVM *jvm, JNIEnv *env) {
    mPJvm = jvm;
}

void attachCurrentThread(JNIEnv *env) {
    JavaVM *jvm = JniManager::getInstance()->getJvm();
    int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if(JNI_OK == status) {
        // 已经attach过了
        return;
    }
    JavaVMAttachArgs args{JNI_VERSION_1_6, nullptr, nullptr};
    jvm->AttachCurrentThread(&env, &args);
}

void detachCurrentThread() {
    JavaVM *jvm = JniManager::getInstance()->getJvm();
    if (jvm) {
        jvm->DetachCurrentThread();
    }
}