#include "mirage_utils.h"

#include <android/window.h>
#include <jni.h>

#include "android_globals.h"

void hideNavigationBar(JavaVM* vm, jobject context) {
    //android_globals_get_window();

    /*JNIEnv* env{};
    //vm->AttachCurrentThread(&env, NULL);
    vm->GetEnv((void**)&env, JNI_VERSION_1_6);

    jclass activityClass = env->FindClass("android/app/NativeActivity");
    jmethodID getWindow = env->GetMethodID(activityClass, "getWindow", "()Landroid/view/Window;");

    jclass windowClass = env->FindClass("android/view/Window");
    jmethodID getDecorView = env->GetMethodID(windowClass, "getDecorView", "()Landroid/view/View;");

    jclass viewClass = env->FindClass("android/view/View");
    jmethodID setSystemUiVisibility = env->GetMethodID(viewClass, "setSystemUiVisibility", "(I)V");

    jobject window = env->CallObjectMethod(context, getWindow);

    jobject decorView = env->CallObjectMethod(window, getDecorView);

    jfieldID flagFullscreenID = env->GetStaticFieldID(viewClass, "SYSTEM_UI_FLAG_FULLSCREEN", "I");
    jfieldID flagHideNavigationID = env->GetStaticFieldID(viewClass, "SYSTEM_UI_FLAG_HIDE_NAVIGATION", "I");
    jfieldID flagImmersiveStickyID = env->GetStaticFieldID(viewClass, "SYSTEM_UI_FLAG_IMMERSIVE_STICKY", "I");

    const int flagFullscreen = env->GetStaticIntField(viewClass, flagFullscreenID);
    const int flagHideNavigation = env->GetStaticIntField(viewClass, flagHideNavigationID);
    const int flagImmersiveSticky = env->GetStaticIntField(viewClass, flagImmersiveStickyID);
    const int flag = flagFullscreen | flagHideNavigation | flagImmersiveSticky;

    env->CallVoidMethod(decorView, setSystemUiVisibility, flag);*/

    //vm->DetachCurrentThread();
}