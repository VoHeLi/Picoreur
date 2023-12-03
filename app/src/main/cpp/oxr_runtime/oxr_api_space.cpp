// Copyright 2019-2020, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Space, space, space, SPAAAAAAAAAAAAAAAAAAAAAAAAAACE!
 * @author Jakob Bornecrantz <jakob@collabora.com>
 * @ingroup oxr_api
 */

#include "mirage_app/mirage_main.h"

#include "oxr_objects.h"

#include "oxr_api_funcs.h"
#include "oxr_api_verify.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>




XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateReferenceSpaces(XrSession session, //PASS TODO : maybe change reference space to stage?
                           uint32_t spaceCapacityInput,
                           uint32_t *spaceCountOutput,
                           XrReferenceSpaceType *spaces){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrEnumerateReferenceSpaces called!");


    return mirageEnumerateReferenceSpaces(session, spaceCapacityInput, spaceCountOutput, spaces);
}


XRAPI_ATTR XrResult XRAPI_CALL // PASS TODO: update bounds?
xrGetReferenceSpaceBoundsRect(XrSession session, XrReferenceSpaceType referenceSpaceType, XrExtent2Df *bounds){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "GetReferenceSpaceBoundsRect called!");


    return mirageGetReferenceSpaceBoundsRect(session, referenceSpaceType, bounds);
}


XRAPI_ATTR XrResult XRAPI_CALL // PASS TODO: Set origin
xrCreateReferenceSpace(XrSession session, const XrReferenceSpaceCreateInfo *createInfo, XrSpace *space){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateReferenceSpace called!");


    return mirageCreateReferenceSpace(session, createInfo, space);
}


XRAPI_ATTR XrResult XRAPI_CALL // PASS TODO : see usages
xrLocateSpace(XrSpace space, XrSpace baseSpace, XrTime time, XrSpaceLocation *location){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrLocateSpace called!");


    return mirageLocateSpace(space, baseSpace, time, location);
}


XRAPI_ATTR XrResult XRAPI_CALL // PASS
xrDestroySpace(XrSpace space){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrDestroySpace called!");


    return mirageDestroySpace(space);
}


XRAPI_ATTR XrResult XRAPI_CALL // PASS TODO : Set Origin?
xrCreateActionSpace(XrSession session, const XrActionSpaceCreateInfo *createInfo, XrSpace *space){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateActionSpace called!");


    return mirageCreateActionSpace(session, createInfo, space);
}