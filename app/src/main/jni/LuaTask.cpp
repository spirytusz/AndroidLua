//
// Created by Administrator on 2019/7/18.
//

#include "LuaTask.h"
#include "JniManager.h"

LuaTask::LuaTask(jstring jBuff) {
    mLuaBuff = jBuff;
    mLuaEngine = new LuaEngine();
    mThreadId = 0;
}

LuaTask::~LuaTask() {
    delete mLuaEngine;
}

void LuaTask::startWork() {
    pthread_create(&mThreadId, NULL, &LuaTask::startWorkInner, (void*)this);
}

void LuaTask::stopWork() {
    mLuaEngine->stopScript();
    mThreadId = 0;
}

void* LuaTask::startWorkInner(void *args) {
    LuaTask* task = (LuaTask*) args;
    JNIEnv* env = nullptr;
    JniManager::getInstance()->attachCurrentThread(env);
    task->mLuaEngine->startScript(task->mLuaBuff, "main");
    JniManager::getInstance()->detachCurrentThread();
    return nullptr;
}

bool LuaTask::isRunning() {
    return mThreadId != 0;
}