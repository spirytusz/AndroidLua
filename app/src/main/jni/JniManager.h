//
// Created by Administrator on 2019/7/19.
//

#ifndef ANDROIDLUA_JNIMANAGER_H
#define ANDROIDLUA_JNIMANAGER_H

#include <jni.h>

class JniManager {

private:
    static JniManager *instance;

public:
    static JniManager *getInstance();

    void initJniManager(JavaVM *jvm, JNIEnv *env);

    JavaVM *getJvm() {
        return mPJvm;
    }

private:
    JavaVM *mPJvm;
};

void attachCurrentThread(JNIEnv *env);

void detachCurrentThread();

#endif //ANDROIDLUA_JNIMANAGER_H
