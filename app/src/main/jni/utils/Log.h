//
// Created by Administrator on 2019/7/18.
//

#ifndef ANDROIDLUA_LOG_H
#define ANDROIDLUA_LOG_H

#include <android/log.h>

#define Log_v(tag, ...) __android_log_print(ANDROID_LOG_VERBOSE, tag, __VA_ARGS__)
#define Log_d(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
#define Log_i(tag, ...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
#define Log_w(tag, ...) __android_log_print(ANDROID_LOG_WARN, tag, __VA_ARGS__)
#define Log_e(tag, ...) __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)

#endif //ANDROIDLUA_LOG_H
