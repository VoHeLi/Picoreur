
#include "mirage_loader.h"
#include <android/log.h>
#include <string>

#include <dlfcn.h>

#define LYNX_LOADER_PATH_FILE "/storage/self/primary/PicoreurLynxLoaderPath.txt"

#include <fstream>
#include <iostream>

XrResult storeLynxOpenXRPath(){

    // Obtenez le chemin du répertoire des bibliothèques natives
    jstring nativeJLibraryDir = (jstring)runtimeJniEnv->CallObjectMethod(runtimeJavaObject, runtimeJniEnv->GetMethodID(runtimeJniEnv->GetObjectClass(runtimeJavaObject), "getNativeDir", "()Ljava/lang/String;"));

    const char* nativeLibraryDir = runtimeJniEnv->GetStringUTFChars(nativeJLibraryDir, NULL);
    const char* libLoc = (std::string(nativeLibraryDir) + std::string("/libopenxr_loader.so")).c_str();

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Writing path to file for other apps to know where it is");

    // Writing path to file for other apps to know where it is
    std::ofstream outfile(LYNX_LOADER_PATH_FILE);
    outfile << libLoc;
    outfile.close();

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Writing path to file successful!");

    return XR_SUCCESS;
}

XrResult loadLynxOpenXR(){
    // Reading path from file written by the runtime
    std::ifstream infile(LYNX_LOADER_PATH_FILE);
    std::string libLoc((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    lynxLoaderHandle = dlopen(libLoc.c_str(), RTLD_NOW);
    if (!lynxLoaderHandle) {
        __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Can't load Lynx OpenXR Loader : %s \n ", dlerror());
        return XrResult::XR_ERROR_HANDLE_INVALID;
    }

    return XrResult::XR_SUCCESS;
}

XrResult loadRuntimeContext(JNIEnv *env, jobject thiz){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Loading Runtime Java Context");
    runtimeJavaObject = thiz;
    runtimeJniEnv = env;

    XrResult  result = storeLynxOpenXRPath();

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "After storeLynxOpenXRPath");

    return result;
}

XrResult m_xrGetInstanceProcAddr(XrInstance instance, const char *name,
                                                PFN_xrVoidFunction *function) {
    if(lynxLoaderHandle == nullptr) loadLynxOpenXR();

    void (*func)(void) = (void (*)(void))dlsym(lynxLoaderHandle, "xrGetInstanceProcAddr");

    PFN_xrGetInstanceProcAddr l_xrGetInstanceProcAddr = (PFN_xrGetInstanceProcAddr)func;

    return l_xrGetInstanceProcAddr(instance, name, function);
}
