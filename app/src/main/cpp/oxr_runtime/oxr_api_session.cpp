// Copyright 2019-2020, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Session entrypoints for the OpenXR state tracker.
 * @author Jakob Bornecrantz <jakob@collabora.com>
 * @ingroup oxr_api
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


#include "oxr_objects.h"

#include "oxr_api_funcs.h"
#include "oxr_api_verify.h"
#include "oxr_chain.h"

#include "mirage_app/mirage_main.h"


XRAPI_ATTR XrResult XRAPI_CALL
xrCreateSession(XrInstance instance, const XrSessionCreateInfo *createInfo, XrSession *out_session) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateSession called!");


    return mirageCreateSession(createInfo, out_session);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrDestroySession(XrSession session) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrDestroySession called!");


    return mirageDestroySession(session);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrBeginSession(XrSession session, const XrSessionBeginInfo *beginInfo) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrBeginSession called!");


    return mirageBeginSession(session, beginInfo);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrEndSession(XrSession session) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEndSession called!");


    return mirageEndSession(session);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrWaitFrame(XrSession session, const XrFrameWaitInfo *frameWaitInfo, XrFrameState *frameState) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrWaitFrame called!");


    return mirageWaitFrame(session, frameWaitInfo, frameState);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrBeginFrame(XrSession session, const XrFrameBeginInfo *frameBeginInfo) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrBeginFrame called!");


    return mirageBeginFrame(session, frameBeginInfo);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrEndFrame(XrSession session, const XrFrameEndInfo *frameEndInfo) //PASS TODO : Check blendmodes and layers
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEndFrame called!");


    return mirageEndFrame(session, frameEndInfo);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrRequestExitSession(XrSession session) //PASS
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrRequestExitSession called!");


    return mirageRequestExitSession(session);
}

XRAPI_ATTR XrResult XRAPI_CALL
xrLocateViews(XrSession session,
                  const XrViewLocateInfo *viewLocateInfo,
                  XrViewState *viewState,
                  uint32_t viewCapacityInput,
                  uint32_t *viewCountOutput,
                  XrView *views) //PASS : TODO add offset to fov
{
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrLocateViews called!");


    return mirageLocateViews(session, viewLocateInfo, viewState, viewCapacityInput, viewCountOutput, views);
}


//TODO : Add Visibilty mask

//TODO : SUPPORT Hand-tracking here