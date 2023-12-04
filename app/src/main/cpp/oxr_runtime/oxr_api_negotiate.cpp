// Copyright 2018-2019, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  File for negotiating with the loader.
 * @author Ryan Pavlik <ryan.pavlik@collabora.com>
 * @author Jakob Bornecrantz <jakob@collabora.com>
 * @ingroup oxr_api
 */

#include <string.h>

#include "oxr_api_funcs.h"
#include "oxr_api_verify.h"

#include "../openxr/loader_interface.h"

#include <android/log.h>
#include <jni.h>


#define PRINT_NEGOTIATE(...)                                                                                           \
	do {                                                                                                           \
        __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Negotiate : %s", __VA_ARGS__);  \
	} while (false)


extern "C"
XRAPI_ATTR XrResult XRAPI_CALL
xrNegotiateLoaderRuntimeInterface(const XrNegotiateLoaderInfo *loaderInfo, XrNegotiateRuntimeRequest *runtimeRequest)
{
    PRINT_NEGOTIATE("xrNegotiateLoaderRuntimeInterface\n");


    // Make sure that we understand the structs passed to this function.
    if (loaderInfo->structType != XR_LOADER_INTERFACE_STRUCT_LOADER_INFO ||
        loaderInfo->structVersion != XR_LOADER_INFO_STRUCT_VERSION ||
        loaderInfo->structSize != sizeof(XrNegotiateLoaderInfo)) {
        PRINT_NEGOTIATE("\tloaderInfo bad!\n");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    // Make sure that we understand the structs passed to this function.
    if (runtimeRequest->structType != XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST ||
        runtimeRequest->structVersion != XR_RUNTIME_INFO_STRUCT_VERSION ||
        runtimeRequest->structSize != sizeof(XrNegotiateRuntimeRequest)) {
        PRINT_NEGOTIATE("\truntimeRequest bad!\n");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    // TODO: properly define what we support
    uint16_t supported_major = XR_VERSION_MAJOR(XR_CURRENT_API_VERSION);

    uint32_t requested_min_major = loaderInfo->minInterfaceVersion;
    uint32_t requested_max_major = loaderInfo->maxInterfaceVersion;

    if (supported_major > requested_max_major || supported_major < requested_min_major) {
        PRINT_NEGOTIATE(
                "\tXRT - OpenXR doesn't support requested version %d <= "
                "%d <= %d\n",
                requested_min_major, supported_major, requested_max_major);
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    runtimeRequest->getInstanceProcAddr = xrGetInstanceProcAddr;
    runtimeRequest->runtimeInterfaceVersion = XR_CURRENT_LOADER_RUNTIME_VERSION;
    runtimeRequest->runtimeApiVersion = XR_CURRENT_API_VERSION;

    PRINT_NEGOTIATE("\tall ok!\n");

    return XR_SUCCESS;
}

JNIEXPORT XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateApiLayerProperties(uint32_t propertyCapacityInput,
                                  uint32_t *propertyCountOutput,
                                  XrApiLayerProperties *properties)
{
    PRINT_NEGOTIATE("xrEnumerateApiLayerProperties");

    /* We have no layers inbuilt. */
    if (propertyCountOutput != NULL) {
        *propertyCountOutput = 0;
    }

    return XR_SUCCESS;
}

/*!
 * @brief Helper define for generating that GetInstanceProcAddr function.
 *
 * Use for functions that should be unconditionally available.
 */
#define ENTRY(funcName)                                                                                                \
	do {                                                                                                           \
		if (strcmp(name, #funcName) == 0) {                                                                    \
			PFN_##funcName ret = &funcName;                                                          \
			*out_function = (PFN_xrVoidFunction)(ret);                                                     \
			return XR_SUCCESS;                                                                             \
		}                                                                                                      \
	} while (false)

/*!
 * @brief Helper define for generating that GetInstanceProcAddr function for
 * conditionally-available functions.
 *
 * Checks the extra condition to e.g. find out if the extension is enabled
 */
#define ENTRY_IF(funcName, extraCondition, message)                                                                    \
	do {                                                                                                           \
		if (strcmp(name, #funcName) == 0) {                                                                    \
			if (extraCondition) {                                                                          \
				PFN_funcName ret = &funcName;                                                  \
				*out_function = (PFN_xrVoidFunction)(ret);                                             \
				return XR_SUCCESS;                                                                     \
			}                                                                                              \
			return XR_ERROR_FUNCTION_UNSUPPORTED;                                                          \
		}                                                                                                      \
	} while (false)

/*!
 * @brief Helper define for generating that GetInstanceProcAddr function for
 * extension-provided functions.
 *
 * Wraps ENTRY_IF for the common case.
 *
 * Pass the function name and the (mixed-case) extension name without the
 * leading XR_.
 */
#define ENTRY_IF_EXT(funcName, short_ext_name)                                                                         \
	ENTRY_IF(funcName, inst->extensions.short_ext_name, "Required extension XR_" #short_ext_name " not enabled")
/*!
 * Handle a non-null instance pointer.
 */
static XrResult
handle_non_null(struct oxr_instance *inst, const char *name, PFN_xrVoidFunction *out_function)
{
    ENTRY(xrGetInstanceProcAddr);
    ENTRY(xrEnumerateInstanceExtensionProperties);
    ENTRY(xrCreateInstance);

    ENTRY(xrDestroyInstance);
    ENTRY(xrGetInstanceProperties);
    ENTRY(xrPollEvent);
    ENTRY(xrResultToString);
    ENTRY(xrStructureTypeToString);
    ENTRY(xrStringToPath);
    ENTRY(xrPathToString);

    ENTRY(xrGetSystem);
    ENTRY(xrGetSystemProperties);
    ENTRY(xrEnumerateEnvironmentBlendModes);
    ENTRY(xrEnumerateViewConfigurations);
    ENTRY(xrGetViewConfigurationProperties);
    ENTRY(xrEnumerateViewConfigurationViews);
    ENTRY(xrGetOpenGLESGraphicsRequirementsKHR);

    ENTRY(xrCreateSession);
    ENTRY(xrDestroySession);
    ENTRY(xrBeginSession);
    ENTRY(xrEndSession);
    ENTRY(xrWaitFrame);
    ENTRY(xrBeginFrame);
    ENTRY(xrEndFrame);
    ENTRY(xrRequestExitSession);
    ENTRY(xrLocateViews);

    ENTRY(xrEnumerateReferenceSpaces);
    ENTRY(xrCreateReferenceSpace);
    ENTRY(xrGetReferenceSpaceBoundsRect);
    ENTRY(xrCreateActionSpace);
    ENTRY(xrLocateSpace);
    ENTRY(xrDestroySpace);



    ENTRY(xrCreateActionSet);
    ENTRY(xrDestroyActionSet);
    ENTRY(xrCreateAction);
    ENTRY(xrDestroyAction);
    ENTRY(xrSuggestInteractionProfileBindings);
    ENTRY(xrAttachSessionActionSets);
    ENTRY(xrGetCurrentInteractionProfile);
    ENTRY(xrGetActionStateBoolean);
    ENTRY(xrGetActionStateFloat);
    ENTRY(xrGetActionStateVector2f);
    ENTRY(xrGetActionStatePose);
    ENTRY(xrSyncActions);
    ENTRY(xrEnumerateBoundSourcesForAction);
    ENTRY(xrGetInputSourceLocalizedName);
    ENTRY(xrApplyHapticFeedback);
    ENTRY(xrStopHapticFeedback);

    ENTRY(xrEnumerateSwapchainFormats);
    ENTRY(xrCreateSwapchain);
    ENTRY(xrDestroySwapchain);
    ENTRY(xrEnumerateSwapchainImages);
    ENTRY(xrAcquireSwapchainImage);
    ENTRY(xrWaitSwapchainImage);
    ENTRY(xrReleaseSwapchainImage);



/*
#ifdef OXR_HAVE_KHR_visibility_mask
    ENTRY_IF_EXT(xrGetVisibilityMaskKHR, KHR_visibility_mask);
#endif // OXR_HAVE_KHR_visibility_mask

#ifdef OXR_HAVE_KHR_convert_timespec_time
    ENTRY_IF_EXT(xrConvertTimespecTimeToTimeKHR, KHR_convert_timespec_time);
	ENTRY_IF_EXT(xrConvertTimeToTimespecTimeKHR, KHR_convert_timespec_time);
#endif // OXR_HAVE_KHR_convert_timespec_time

#ifdef OXR_HAVE_KHR_win32_convert_performance_counter_time
    ENTRY_IF_EXT(xrConvertWin32PerformanceCounterToTimeKHR, KHR_win32_convert_performance_counter_time);
	ENTRY_IF_EXT(xrConvertTimeToWin32PerformanceCounterKHR, KHR_win32_convert_performance_counter_time);
#endif // OXR_HAVE_KHR_win32_convert_performance_counter_time

#ifdef OXR_HAVE_KHR_android_thread_settings
    ENTRY_IF_EXT(xrSetAndroidApplicationThreadKHR, KHR_android_thread_settings);
#endif // XR_HAVE_KHR_android_thread_settings

#ifdef OXR_HAVE_EXT_performance_settings
    ENTRY_IF_EXT(xrPerfSettingsSetPerformanceLevelEXT, EXT_performance_settings);
#endif // OXR_HAVE_EXT_performance_settings

#ifdef OXR_HAVE_EXT_thermal_query
    ENTRY_IF_EXT(xrThermalGetTemperatureTrendEXT, EXT_thermal_query);
#endif // OXR_HAVE_EXT_thermal_query

#ifdef OXR_HAVE_EXT_hand_tracking
    ENTRY_IF_EXT(xrCreateHandTrackerEXT, EXT_hand_tracking);
	ENTRY_IF_EXT(xrDestroyHandTrackerEXT, EXT_hand_tracking);
	ENTRY_IF_EXT(xrLocateHandJointsEXT, EXT_hand_tracking);
#endif

#ifdef OXR_HAVE_MNDX_force_feedback_curl
    ENTRY_IF_EXT(xrApplyForceFeedbackCurlMNDX, MNDX_force_feedback_curl);
#endif

#ifdef OXR_HAVE_FB_display_refresh_rate
    ENTRY_IF_EXT(xrEnumerateDisplayRefreshRatesFB, FB_display_refresh_rate);
	ENTRY_IF_EXT(xrGetDisplayRefreshRateFB, FB_display_refresh_rate);
	ENTRY_IF_EXT(xrRequestDisplayRefreshRateFB, FB_display_refresh_rate);
#endif

#ifdef OXR_HAVE_EXT_debug_utils
    ENTRY_IF_EXT(xrSetDebugUtilsObjectNameEXT, EXT_debug_utils);
	ENTRY_IF_EXT(xrCreateDebugUtilsMessengerEXT, EXT_debug_utils);
	ENTRY_IF_EXT(xrDestroyDebugUtilsMessengerEXT, EXT_debug_utils);
	ENTRY_IF_EXT(xrSubmitDebugUtilsMessageEXT, EXT_debug_utils);
	ENTRY_IF_EXT(xrSessionBeginDebugUtilsLabelRegionEXT, EXT_debug_utils);
	ENTRY_IF_EXT(xrSessionEndDebugUtilsLabelRegionEXT, EXT_debug_utils);
	ENTRY_IF_EXT(xrSessionInsertDebugUtilsLabelEXT, EXT_debug_utils);
#endif // OXR_HAVE_EXT_debug_utils

#ifdef OXR_HAVE_KHR_opengl_es_enable
    ENTRY_IF_EXT(xrGetOpenGLESGraphicsRequirementsKHR, KHR_opengl_es_enable);
#endif // OXR_HAVE_KHR_opengl_es_enable

#ifdef OXR_HAVE_KHR_visibility_mask
    ENTRY_IF_EXT(xrGetVisibilityMaskKHR, KHR_visibility_mask);
#endif // OXR_HAVE_KHR_visibility_mask
*/

    /*
     * Not logging here because there's no need to loudly advertise
     * which extensions the loader knows about (it calls this on
     * every known function) that we don't implement.
     */
    return XR_ERROR_FUNCTION_UNSUPPORTED;
}

/*!
 * Special case a null instance pointer.
 */
static XrResult
handle_null(const char *name, PFN_xrVoidFunction *out_function)
{
    ENTRY(xrCreateInstance);
    ENTRY(xrEnumerateInstanceExtensionProperties);
    ENTRY(xrEnumerateApiLayerProperties);
    ENTRY(xrInitializeLoaderKHR);


    /*
     * This is fine to log, since there should not be other
     * null-instance calls.
     */
    return XR_ERROR_FUNCTION_UNSUPPORTED;
}

JNIEXPORT XRAPI_ATTR XrResult XRAPI_CALL
xrGetInstanceProcAddr(XrInstance instance, const char *name, PFN_xrVoidFunction *function)
{

    // We need to set this unconditionally, per the spec.
    *function = NULL;

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrGetInstanceProcAddr : %s", name);

    if (instance == XR_NULL_HANDLE) {
        return handle_null(name, function);
    }


    struct oxr_instance *inst;

    if (instance == 0) {
        return XR_ERROR_HANDLE_INVALID;
    }
    inst = (struct oxr_instance *) ((uintptr_t) instance);

    return handle_non_null(inst, name, function);
}
