#include "oxr_api_funcs.h"
#include "openxr/openxr_platform.h"
#include "openxr/openxr_platform_defines.h"

#include <android/log.h>
#include <string>

#include "android_globals.h"
#include "oxr_extension_support.h"
#include "oxr_api_verify.h"
#include "oxr_chain.h"
#include "oxr_objects.h"

#include "mirage_app/mirage_main.h"

#include <cstdlib>
#include <chrono>
#include <ctime>


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

static XrResult
oxr_check_android_extensions(const XrInstanceCreateInfo *createInfo, const struct oxr_extension_status *extensions)
{
    // We need the XR_KHR_android_create_instance extension.
    if (!extensions->KHR_android_create_instance) {

        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : (createInfo->enabledExtensionNames) Mandatory platform-specific extension XR_KHR_android_create_instance not specified");

        return XR_ERROR_INITIALIZATION_FAILED;
    }

    {
        // Verify that it exists and is populated.
        XrInstanceCreateInfoAndroidKHR const *createInfoAndroid = OXR_GET_INPUT_FROM_CHAIN(
                createInfo, XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR, XrInstanceCreateInfoAndroidKHR);
        if (createInfoAndroid == NULL) {
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : (createInfo->next...) Did not find XrInstanceCreateInfoAndroidKHR in chain");

            return XR_ERROR_VALIDATION_FAILURE;
        }
        if (createInfoAndroid->applicationVM == NULL) {
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : (createInfo->next...->applicationVM) applicationVM must be populated");
            return XR_ERROR_VALIDATION_FAILURE;
        }
        if (createInfoAndroid->applicationActivity == NULL) {
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : (createInfo->next...->applicationActivity) applicationActivity must be populated");
            return XR_ERROR_VALIDATION_FAILURE;
        }
    }
    return XR_SUCCESS;
}

extern "C"
//! OpenXR API function @ep{xrCreateInstance}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateInstance(const XrInstanceCreateInfo *createInfo, XrInstance *out_instance){


    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance called!");


    XrResult ret;

    if(createInfo == nullptr){
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : createInfo nullptr error!");
        return XR_ERROR_VALIDATION_FAILURE;
    }

    if(createInfo->type != XR_TYPE_INSTANCE_CREATE_INFO){
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : createInfo nullptr error!");
        return XR_ERROR_VALIDATION_FAILURE;
    }

    const uint32_t major = XR_VERSION_MAJOR(XR_CURRENT_API_VERSION);
    const uint32_t minor = XR_VERSION_MINOR(XR_CURRENT_API_VERSION);
    const uint32_t patch = XR_VERSION_PATCH(XR_CURRENT_API_VERSION);
    (void)patch; // Not used for now.


    if (createInfo->applicationInfo.apiVersion < XR_MAKE_VERSION(major, minor, 0)) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : Cannot satisfy request for version less than %d.%d.%d", major, minor, 0);

        return XR_ERROR_API_VERSION_UNSUPPORTED;
    }

    /*
     * This is a slight fib, to let us approximately run things between 1.0
     * and 2.0
     */
    if (createInfo->applicationInfo.apiVersion >= XR_MAKE_VERSION(2, 0, 0)) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : Cannot satisfy request for version: too high");
        return XR_ERROR_API_VERSION_UNSUPPORTED;
    }

    // To be passed into verify and instance creation.
    struct oxr_extension_status extensions;
    std::memset(&extensions, 0, sizeof(extensions));

    /*
     * Check that all extension names are recognized, so oxr_instance_create
     * doesn't need to check for bad extension names.
     *
     * Also fill out the oxr_extension_status struct at the same time.
     */
#define CHECK_EXT_NAME(mixed_case, all_caps)                                                                           \
	if (strcmp(createInfo->enabledExtensionNames[i], XR_##all_caps##_EXTENSION_NAME) == 0) {                       \
		extensions.mixed_case = true;                                                                          \
		continue;                                                                                              \
	}
    for (uint32_t i = 0; i < createInfo->enabledExtensionCount; ++i) {
        OXR_EXTENSION_SUPPORT_GENERATE(CHECK_EXT_NAME)

        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrCreateInstance : (createInfo->enabledExtensionNames[%d]) Unrecognized extension name '%s'", i,
                            createInfo->enabledExtensionNames[i]);

        return XR_ERROR_EXTENSION_NOT_PRESENT;
    }

    ret = oxr_verify_extensions(&extensions);
    if (ret != XR_SUCCESS) {
        return ret;
    }


    ret = oxr_check_android_extensions(createInfo, &extensions);
	if (ret != XR_SUCCESS) {
		return ret;
	}

    oxr_instance *inst = NULL;

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto currentTimeMicros = std::chrono::duration_cast<std::chrono::microseconds>(currentTime.time_since_epoch()).count();
    srand(static_cast<unsigned int>(currentTimeMicros));
    int randomNumber = rand();

    inst = new oxr_instance(randomNumber);

    *out_instance = ((XrInstance)(uint64_t)(intptr_t)(inst));

    //TODO LAUNCH REAL INSTANCE

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance calling mirage!");

    return initializeMirageApp(android_globals_get_context(), android_globals_get_vm());

}