
#include <algorithm>
#include "mirage_main.h"

#include <android/log.h>
#include "platformplugin.h"

#include <string>
#include <vector>


void CreateInstanceInternal(const std::shared_ptr<IPlatformPlugin>& platformPlugin) {
    // Create union of extensions required by platform and graphics plugins.
    std::vector<const char*> extensions;/* = {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME, XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME};*/

    // Transform platform and graphics extension std::strings to C strings.
    const std::vector<std::string> platformExtensions = platformPlugin->GetInstanceExtensions();
    std::transform(platformExtensions.begin(), platformExtensions.end(), std::back_inserter(extensions),
                   [](const std::string& ext) { return ext.c_str(); });
    const std::vector<std::string> graphicsExtensions = {XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME};
    std::transform(graphicsExtensions.begin(), graphicsExtensions.end(), std::back_inserter(extensions),
                   [](const std::string& ext) { return ext.c_str(); });



    XrInstanceCreateInfo createInfo{XR_TYPE_INSTANCE_CREATE_INFO};
    createInfo.next = platformPlugin->GetInstanceCreateExtension();
    createInfo.enabledExtensionCount = (uint32_t)extensions.size();
    createInfo.enabledExtensionNames = extensions.data();

    strcpy(createInfo.applicationInfo.applicationName, "Picoreur Mirage");
    createInfo.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;

    //DEBUG XRINSTANCECREATEINFO :
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo type : %d", createInfo.type);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo createFlags : %p", createInfo.createFlags);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo applicationInfo : %p", createInfo.applicationInfo);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo enabledExtensionCount : %d", createInfo.enabledExtensionCount);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo enableApiLayerCount : %d", createInfo.enabledApiLayerCount);

    for(int i = 0; i < createInfo.enabledExtensionCount; i++){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo enabled Extension : %s", createInfo.enabledExtensionNames[i]);
    }

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Before xrCreateInstance Mirage call");

    PFN_xrCreateInstance l_xrCreateInstance;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(nullptr, "xrCreateInstance", (PFN_xrVoidFunction*)&l_xrCreateInstance))){
        l_xrCreateInstance(&createInfo, &mirageInstance);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrCreateInstance not loaded from Lynx libopenxr_loader.so");
    }


}

void CreateInstance() {

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Starting Mirage Instance");
    CreateInstanceInternal(miragePlatformPlugin);
}

XrResult initializeMirageApp(void* vm, void* clazz){

    miragePlatformPlugin = CreatePlatformPlugin(vm, clazz);

    //Initialize the loader
    PFN_xrInitializeLoaderKHR initializeLoader = nullptr;
    if (XR_SUCCEEDED(
            m_xrGetInstanceProcAddr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)(&initializeLoader)))) {
        XrLoaderInitInfoAndroidKHR loaderInitInfoAndroid = {XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR};
        loaderInitInfoAndroid.applicationVM = vm;
        loaderInitInfoAndroid.applicationContext = clazz;

        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : loaderInitInfoAndroid.applicationVM : %p", loaderInitInfoAndroid.applicationContext);
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : loaderInitInfoAndroid.applicationContext : %p", loaderInitInfoAndroid.applicationVM);

        initializeLoader((const XrLoaderInitInfoBaseHeaderKHR*)&loaderInitInfoAndroid);
    }

    CreateInstance();

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Mirage Instance successfully created!");
    return XR_SUCCESS;
}

