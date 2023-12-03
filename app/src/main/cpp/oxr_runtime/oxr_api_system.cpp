// Copyright 2018-2020, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Holds system related entrypoints.
 * @author Jakob Bornecrantz <jakob@collabora.com>
 * @ingroup oxr_api
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mirage_app/mirage_main.h"
#include "oxr_extension_support.h"

#include "oxr_objects.h"

#include "oxr_api_funcs.h"
#include "oxr_api_verify.h"


/*!
 * A helper define that verifies the systemId.
 */
#define OXR_VERIFY_SYSTEM_AND_GET(log, inst, sysId, system)                                                            \
	struct oxr_system *system = NULL;                                                                              \
	do {                                                                                                           \
		XrResult ret = oxr_system_get_by_id(log, inst, sysId, &system);                                        \
		if (ret != XR_SUCCESS) {                                                                               \
			return ret;                                                                                    \
		}                                                                                                      \
		assert(system != NULL);                                                                                \
	} while (false)

#define OXR_VERIFY_XSYSC(LOG, SYS)                                                                                     \
	do {                                                                                                           \
		if ((SYS)->xsysc == NULL) {                                                                            \
			return oxr_error((LOG), XR_ERROR_VALIDATION_FAILURE,                                           \
			                 " Function can not be called when specifically not asking for graphics");     \
		}                                                                                                      \
	} while (false)

XRAPI_ATTR XrResult XRAPI_CALL
xrGetSystem(XrInstance instance, const XrSystemGetInfo *getInfo, XrSystemId *systemId)
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrGetSystem called!");

    if(instance == nullptr){
        return XR_ERROR_INSTANCE_LOST;
    }

    if(getInfo == nullptr){
        return XR_ERROR_NAME_INVALID;
    }

    if(getInfo->type != XR_TYPE_SYSTEM_GET_INFO){
        return XR_ERROR_NAME_INVALID;
    }

    if(getInfo->formFactor != XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY ){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrGetSystem : not asking for HMD but : %d", getInfo->formFactor);
    }

    return getMirageSystem(getInfo, systemId);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrGetSystemProperties(XrInstance instance, XrSystemId systemId, XrSystemProperties *properties)
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrGetSystemProperties called!");

    if(instance == nullptr){
        return XR_ERROR_INSTANCE_LOST;
    }

    /*if(properties == nullptr){
        return XR_ERROR_NAME_INVALID;
    }

    if(properties->type != XR_TYPE_SYSTEM_GET_INFO){
        return XR_ERROR_NAME_INVALID;
    }

    if(systemId == 0){
        return XR_ERROR_HANDLE_INVALID;
    }*/

    XrResult result = getMirageSystemProperties(systemId, properties);

    if(properties != nullptr){
        properties->vendorId = VENDOR_ID;
    }

    return result;
}

XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateViewConfigurations(XrInstance instance,
                                  XrSystemId systemId,
                                  uint32_t viewConfigurationTypeCapacityInput,
                                  uint32_t *viewConfigurationTypeCountOutput,
                                  XrViewConfigurationType *viewConfigurationTypes)
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateViewConfigurations called!");


    return mirageEnumerateViewConfigurations(systemId,viewConfigurationTypeCapacityInput, viewConfigurationTypeCountOutput, viewConfigurationTypes);
}

XRAPI_ATTR XrResult XRAPI_CALL //TODO ADD MR LATER, CHANGE MODE, PASS FOR NOW
xrEnumerateEnvironmentBlendModes(XrInstance instance,
                                     XrSystemId systemId,
                                     XrViewConfigurationType viewConfigurationType,
                                     uint32_t environmentBlendModeCapacityInput,
                                     uint32_t *environmentBlendModeCountOutput,
                                     XrEnvironmentBlendMode *environmentBlendModes)
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateEnvironmentBlendModes called!");

    /*if(instance == nullptr){
        return XR_ERROR_INSTANCE_LOST;
    }

    if(environmentBlendModeCapacityInput == 0 || environmentBlendModeCountOutput == nullptr || environmentBlendModes == nullptr){
        return XR_ERROR_HANDLE_INVALID;
    }

    if(systemId == 0){
        return XR_ERROR_HANDLE_INVALID;
    }

    if (viewConfigurationType != XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrEnumerateEnvironmentBlendModes :(viewConfigurationType == 0x%08x) unsupported view configuration type",
                viewConfigurationType);

        return XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED;
    }

    *environmentBlendModeCountOutput = 1;
    environmentBlendModes[0] = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateEnvironmentBlendModes success!");

    return XR_SUCCESS;*/

    return mirageEnumerateEnvironmentBlendModes(systemId, viewConfigurationType, environmentBlendModeCapacityInput, environmentBlendModeCountOutput, environmentBlendModes);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrGetViewConfigurationProperties(XrInstance instance,
                                     XrSystemId systemId,
                                     XrViewConfigurationType viewConfigurationType,
                                     XrViewConfigurationProperties *configurationProperties) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrGetViewConfigurationProperties called!");


    return mirageGetViewConfigurationProperties(systemId,viewConfigurationType, configurationProperties);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateViewConfigurationViews(XrInstance instance,
                                      XrSystemId systemId,
                                      XrViewConfigurationType viewConfigurationType,
                                      uint32_t viewCapacityInput,
                                      uint32_t *viewCountOutput,
                                      XrViewConfigurationView *views) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateViewConfigurationViews called!");


    return mirageEnumerateViewConfigurationViews(systemId, viewConfigurationType, viewCapacityInput, viewCountOutput, views);
}


/*
 *
 * OpenGL ES
 *
 */


XRAPI_ATTR XrResult XRAPI_CALL
xrGetOpenGLESGraphicsRequirementsKHR(XrInstance instance,
                                         XrSystemId systemId,
                                         XrGraphicsRequirementsOpenGLESKHR *graphicsRequirements)
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrGetOpenGLESGraphicsRequirementsKHR called!");


	/*OXR_TRACE_MARKER();

	struct oxr_instance *inst;
	struct oxr_logger log;
	OXR_VERIFY_INSTANCE_AND_INIT_LOG(&log, instance, inst, "xrGetOpenGLESGraphicsRequirementsKHR");
	OXR_VERIFY_ARG_TYPE_AND_NOT_NULL(&log, graphicsRequirements, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR);
	OXR_VERIFY_SYSTEM_AND_GET(&log, inst, systemId, sys);
	OXR_VERIFY_XSYSC(&log, sys);

	struct xrt_api_requirements ver;

	xrt_gfx_gles_get_versions(&ver);

	graphicsRequirements->minApiVersionSupported = XR_MAKE_VERSION(ver.min_major, ver.min_minor, ver.min_patch);
	graphicsRequirements->maxApiVersionSupported = XR_MAKE_VERSION(ver.max_major, ver.max_minor, ver.max_patch);

	sys->gotten_requirements = true;*/

	return mirageGetOpenGLESGraphicsRequirementsKHR(systemId, graphicsRequirements);
}


