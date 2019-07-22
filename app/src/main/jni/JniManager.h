//
// Created by Administrator on 2019/7/19.
//

#ifndef ANDROIDLUA_JNIMANAGER_H
#define ANDROIDLUA_JNIMANAGER_H

#include <jni.h>
#include <string>
#include <map>
#include "list"
#include "utils/Log.h"
#include "LuaEngine.h"

class JniManager {

private:
    static JniManager *instance;

public:
    static JniManager *getInstance();

    void initJniManager(JavaVM *jvm, JNIEnv *env);

    JavaVM *getJvm() {
        return mPJvm;
    }

    void attachCurrentThread(JNIEnv *env);

    void detachCurrentThread();

    jclass getInRefClass(char *className) {
        auto it = classMapper.find(className);
        if (it != classMapper.end()) {
            return it->second;
        } else {
            return NULL;
        }
    }

private:
    JavaVM *mPJvm;
    std::map<std::string, jclass> classMapper;
    std::list<char *> classes;

    void inRefJavaClass(JNIEnv *env);

    JniManager() {
        classes.push_back("com/zspirytus/androidlua/shell/ShellBridge");
    }

    ~JniManager() {
        JNIEnv *env;
        mPJvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        for (char *className: classes) {
            env->DeleteGlobalRef(classMapper[className]);
        }
        delete mPJvm;
    };
};

#endif //ANDROIDLUA_JNIMANAGER_H
