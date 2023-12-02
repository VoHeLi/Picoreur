#include <jni.h>

#include <android/log.h>

#include "mirage_app/mirage_loader.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_picoreur_runtime_PicoreurService_loadRuntimeJNI(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Service launched");
    XrResult res = loadRuntimeContext(env, thiz);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "loadRuntime JNI OK");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_picoreur_runtime_MainActivity_sayHello(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "App launched.");
}