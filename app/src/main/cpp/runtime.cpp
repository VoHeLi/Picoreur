#include <jni.h>

#include <android/log.h>

#include "mirage_app/mirage_loader.h"
#include "mirage_app/mirage_main.h"

#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_picoreur_runtime_PicoreurService_loadRuntimeJNI(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Service launched");
    XrResult res = loadRuntimeContext(env, thiz);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "loadRuntime JNI OK");

    JavaVM* jvm;
    env->GetJavaVM(&jvm);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "WTF IS THAT JVM: %p", jvm);


    jobject context = (jobject)env->CallObjectMethod(thiz, env->GetMethodID(env->GetObjectClass(thiz), "getContext",
                                                                             "()Landroid/content/Context;"));
    void* contextAddr = env->GetDirectBufferAddress(context);


    //jvm->AttachCurrentThread(&env, nullptr);

    //jvm->AttachCurrentThread(env);
    //initializeMirageApp(static_cast<void *>(jvm), /*contextAddr*/nullptr);


}

extern "C"
JNIEXPORT void JNICALL
Java_com_picoreur_runtime_MainActivity_sayHello(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "App launched.");
}