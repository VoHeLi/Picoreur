#include "oxr_api_funcs.h"
#include "openxr/openxr_platform.h"

#include <android/log.h>

#include "android_globals.h"
#include "oxr_extension_support.h"

#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])

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


#define MAKE_EXTENSION_PROPERTIES(mixed_case, all_caps)                                                                \
	{XR_TYPE_EXTENSION_PROPERTIES, NULL, XR_##all_caps##_EXTENSION_NAME, XR_##mixed_case##_SPEC_VERSION},

static const XrExtensionProperties extension_properties[] = {OXR_EXTENSION_SUPPORT_GENERATE(MAKE_EXTENSION_PROPERTIES)};



//! OpenXR API function @ep{xrEnumerateInstanceExtensionProperties}
XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateInstanceExtensionProperties(const char *layerName,
                                       uint32_t propertyCapacityInput,
                                       uint32_t *propertyCountOutput,
                                       XrExtensionProperties *properties){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateInstanceExtensionProperties called!");

    if (propertyCountOutput == __null) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "propertyCountOutput null");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    *propertyCountOutput = ARRAY_SIZE(extension_properties);
    if (propertyCapacityInput == 0) { return XR_SUCCESS; }
    if (propertyCapacityInput < ARRAY_SIZE(extension_properties)) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "propertyCapacityInput insufficiant : %s", propertyCapacityInput);
        return XR_ERROR_SIZE_INSUFFICIENT;
    }
    for (uint32_t i = 0; i < ARRAY_SIZE(extension_properties); i++) {
        (properties)[i] = (extension_properties)[i];
    }

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateInstanceExtensionProperties success!");

    return XR_SUCCESS;

}

//! OpenXR API function @ep{xrCreateInstance}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateInstance(const XrInstanceCreateInfo *createInfo, XrInstance *instance){
 __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance called!");
}