#include "oxr_api_funcs.h"
#include "openxr/openxr_platform.h"

#include <android/log.h>

#include "android_globals.h"

//! OpenXR API function @ep{xrInitializeLoaderKHR}
 XRAPI_ATTR XrResult XRAPI_CALL
xrInitializeLoaderKHR(const XrLoaderInitInfoBaseHeaderKHR *loaderInitInfo){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrInitializeLoaderKHR called!");

    const XrLoaderInitInfoAndroidKHR *initInfoAndroid = (XrLoaderInitInfoAndroidKHR*)loaderInitInfo;

    if (initInfoAndroid == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Did not find XrLoaderInitInfoAndroidKHR");

    }
    if (initInfoAndroid->applicationVM == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "applicationVM must be populated");

    }
    if (initInfoAndroid->applicationContext == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "applicationContext must be populated");

    }

    android_globals_store_vm_and_context((_JavaVM*)initInfoAndroid->applicationVM, initInfoAndroid->applicationContext);


    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrInitializeLoaderKHR success!");
    return XR_SUCCESS;

}

//! OpenXR API function @ep{xrEnumerateInstanceExtensionProperties}
XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateInstanceExtensionProperties(const char *layerName,
                                       uint32_t propertyCapacityInput,
                                       uint32_t *propertyCountOutput,
                                       XrExtensionProperties *properties){
 __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateInstanceExtensionProperties called!");
}

//! OpenXR API function @ep{xrCreateInstance}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateInstance(const XrInstanceCreateInfo *createInfo, XrInstance *instance){
 __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance called!");
}