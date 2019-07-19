//
// Created by Administrator on 2019/7/18.
//

#include "LuaTask.h"

LuaTask::LuaTask(const char *buff) {
    mLuaBuff = buff;
    mLuaEngine = new LuaEngine();
    mThreadId = 0;
}

LuaTask::~LuaTask() {
    delete mLuaEngine;
    delete mLuaBuff;
}

void LuaTask::startWork() {
    pthread_create(&mThreadId, NULL, (void *(*)(void *))&LuaTask::startWorkInner, this);
}

void LuaTask::stopWork() {
    mLuaEngine->stopScript();
    mThreadId = 0;
}

void* LuaTask::startWorkInner(LuaTask *task) {
    task->mLuaEngine->startScript(task->mLuaBuff, "main");
    return nullptr;
}

bool LuaTask::isRunning() {
    return mThreadId != 0;
}