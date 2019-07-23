
#include "shell.h"

int CPrintMsg(lua_State *L) {
    const char *msg = lua_tostring(L, 1);
    Log_d("Shell", "CPrintMsg: %s", msg);
    return 0;
}

int sleepMilliseconds(lua_State *L) {
    int milliseconds = static_cast<int>(lua_tointeger(L, 1));
    usleep(static_cast<useconds_t>(milliseconds * 1000));
    return 0;
}

int sleepSeconds(lua_State *L) {
    int second = static_cast<int>(lua_tointeger(L, 1));
    for (int i = 0; i < second; i++) {
        sleep(1);
    }
    return 0;
}

int getString(lua_State *L) {
    JNIEnv *env;
    JniManager::getInstance()->getJvm()->GetEnv((void **) &env, JNI_VERSION_1_6);
    jclass clazz = JniManager::getInstance()->getInRefClass(
            "com/zspirytus/androidlua/shell/ShellBridge");
    if (!clazz) {
        Log_d(LOG_TAG, "class not found!");
        return 0;
    }
    jmethodID methodId = env->GetStaticMethodID(clazz, "getStringFromKotlinLayer",
                                                "()Ljava/lang/String;");
    if (!methodId) {
        Log_d(LOG_TAG, "method %s not found!", "getStringFromStaticJavaMethod");
        return 0;
    }
    jstring jStr = (jstring) env->CallStaticObjectMethod(clazz, methodId);
    const char *cStr = env->GetStringUTFChars(jStr, NULL);
    lua_pushstring(L, cStr);
    env->ReleaseStringUTFChars(jStr, cStr);
    env->DeleteLocalRef(jStr);
    return 1;
}

int getData(lua_State *L) {
    JNIEnv *env;
    JniManager::getInstance()->getJvm()->GetEnv((void **) &env, JNI_VERSION_1_6);
    jclass clazz = JniManager::getInstance()->getInRefClass(
            "com/zspirytus/androidlua/shell/ShellBridge");
    if (!clazz) {
        Log_d(LOG_TAG, "class not found!");
        return 0;
    }
    jmethodID methodId = env->GetStaticMethodID(clazz, "getScriptPkgData",
                                                "(Ljava/lang/String;)[B");
    if (!methodId) {
        Log_d(LOG_TAG, "method %s not found!", "getScriptPkgData");
        return 0;
    }
    jstring dataPath = env->NewStringUTF(lua_tostring(L, 1));
    jbyteArray jba = (jbyteArray) env->CallStaticObjectMethod(clazz, methodId, dataPath);
    int len = env->GetArrayLength (jba);
    char* cStr = new char[len + 1];
    env->GetByteArrayRegion (jba, 0, len, reinterpret_cast<jbyte*>(cStr));
    cStr[len] = '\0';
    lua_pushstring(L, cStr);
    env->ReleaseByteArrayElements(jba, (jbyte*) cStr, JNI_ABORT);
    env->DeleteLocalRef(jba);
    env->DeleteLocalRef(dataPath);
    return 1;
}