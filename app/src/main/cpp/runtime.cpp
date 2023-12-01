#include <jni.h>

#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_picoreur_runtime_PicoreurService_sayHello(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "HELLO FROM SERVICE!!!");
}
extern "C"
JNIEXPORT void JNICALL
Java_com_picoreur_runtime_MainActivity_sayHello(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "HELLO!!!");
}