//TODO COMPLETE FILE

#include "oxr_api_verify.h"
#include "oxr_extension_support.h"
#include "oxr_api_funcs.h"

#include <android/log.h>

XrResult
oxr_verify_extensions(const struct oxr_extension_status *extensions)
{

    if (extensions->EXT_dpad_binding && !extensions->KHR_binding_modification) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "XR_EXT_dpad_binding requires XR_KHR_binding_modification");
        return XR_ERROR_VALIDATION_FAILURE;
    }

    return XR_SUCCESS;
}

