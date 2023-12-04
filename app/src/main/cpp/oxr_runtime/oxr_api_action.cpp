//TODO EMULATE ACTIONSETS FOR CONTROLLERS

#include "oxr_api_funcs.h"
#include <openxr/openxr_runtime.h>

#include <android/log.h>

#include "mirage_app/mirage_main.h"
#include "controllers/controllers_binding.h"

#define PASS_MIRAGE(function, ...) __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", #function); \
XrResult res = mirage##function(__VA_ARGS__); \
__android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called with result : %p", #function, res);\
return res;

//! OpenXR API function @ep{xrCreateActionSet}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateActionSet(XrInstance instance, const XrActionSetCreateInfo *createInfo, XrActionSet *actionSet){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "mirageCreateActionSet : %s", createInfo->actionSetName);

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", "CreateActionSet");


    XrResult result = mirageCreateActionSet(createInfo, actionSet);
    if(result != XR_SUCCESS){
        return result;
    }

    TryRegisterActionSet(*actionSet, createInfo->actionSetName);

    return result;
}

//! OpenXR API function @ep{xrDestroyActionSet}
XRAPI_ATTR XrResult XRAPI_CALL
xrDestroyActionSet(XrActionSet actionSet){
    PASS_MIRAGE(DestroyActionSet, actionSet);
}

//! OpenXR API function @ep{xrCreateAction}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateAction(XrActionSet actionSet, const XrActionCreateInfo *createInfo, XrAction *action){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "mirageCreateAction : %s", createInfo->actionName);

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", "CreateAction");
    XrResult result = mirageCreateAction(actionSet, createInfo, action);

    if(result != XR_SUCCESS){
        return result;
    }

    TryRegisterAction(*action, createInfo->actionName);

    return result;
}

//! OpenXR API function @ep{xrDestroyAction}
XRAPI_ATTR XrResult XRAPI_CALL
xrDestroyAction(XrAction action){
    PASS_MIRAGE(DestroyAction, action);
}

//! OpenXR API function @ep{xrSuggestInteractionProfileBindings}
XRAPI_ATTR XrResult XRAPI_CALL
xrSuggestInteractionProfileBindings(XrInstance instance,
                                    const XrInteractionProfileSuggestedBinding *suggestedBindings){

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "xrSuggestInteractionProfileBindings called!");
    return GetControllerDefaultBinding(suggestedBindings);

    //PASS_MIRAGE(SuggestInteractionProfileBindings, suggestedBindings);
}

//! OpenXR API function @ep{xrAttachSessionActionSets}
XRAPI_ATTR XrResult XRAPI_CALL
xrAttachSessionActionSets(XrSession session, const XrSessionActionSetsAttachInfo *bindInfo){
    PASS_MIRAGE(AttachSessionActionSets, session, bindInfo);
}

//! OpenXR API function @ep{xrGetCurrentInteractionProfile}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetCurrentInteractionProfile(XrSession session,
                               XrPath topLevelUserPath,
                               XrInteractionProfileState *interactionProfile){
    PASS_MIRAGE(GetCurrentInteractionProfile, session, topLevelUserPath, interactionProfile);
}

//! OpenXR API function @ep{xrGetActionStateBoolean}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetActionStateBoolean(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateBoolean *data){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOCO", "xrGetActionStateBoolean : %p %p", getInfo->action, getInfo->subactionPath);
    PASS_MIRAGE(GetActionStateBoolean, session, getInfo, data);
}

//! OpenXR API function @ep{xrGetActionStateFloat}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetActionStateFloat(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateFloat *data){
    PASS_MIRAGE(GetActionStateFloat, session, getInfo, data);
}

//! OpenXR API function @ep{xrGetActionStateVector2f}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetActionStateVector2f(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateVector2f *data){
    PASS_MIRAGE(GetActionStateVector2f, session, getInfo, data);
}

//! OpenXR API function @ep{xrGetActionStatePose}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetActionStatePose(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStatePose *data){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOCO", "xrGetActionStatePose : %p %p", getInfo->action, getInfo->subactionPath); //subaction = main, action = interaction
    //PASS_MIRAGE(GetActionStatePose, session, getInfo, data);

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", "GetActionStatePose");
    XrResult result = mirageGetActionStatePose(session, getInfo, data);

    data->isActive = XR_TRUE; // TO MAKE CONTROLLER ACTIVE, TODO REFACTOR,

    return result;
}

//! OpenXR API function @ep{xrSyncActions}
XRAPI_ATTR XrResult XRAPI_CALL
xrSyncActions(XrSession session, const XrActionsSyncInfo *syncInfo){
    PASS_MIRAGE(SyncActions, session, syncInfo);
}

//! OpenXR API function @ep{xrEnumerateBoundSourcesForAction}
XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateBoundSourcesForAction(XrSession session,
                                 const XrBoundSourcesForActionEnumerateInfo *enumerateInfo,
                                 uint32_t sourceCapacityInput,
                                 uint32_t *sourceCountOutput,
                                 XrPath *sources){
    PASS_MIRAGE(EnumerateBoundSourcesForAction, session, enumerateInfo, sourceCapacityInput, sourceCountOutput, sources);
}

//! OpenXR API function @ep{xrApplyHapticFeedback}
XRAPI_ATTR XrResult XRAPI_CALL
xrApplyHapticFeedback(XrSession session,
                      const XrHapticActionInfo *hapticActionInfo,
                      const XrHapticBaseHeader *hapticEvent){
    PASS_MIRAGE(ApplyHapticFeedback, session, hapticActionInfo, hapticEvent);
}

//! OpenXR API function @ep{xrStopHapticFeedback}
XRAPI_ATTR XrResult XRAPI_CALL
xrStopHapticFeedback(XrSession session, const XrHapticActionInfo *hapticActionInfo){
    PASS_MIRAGE(StopHapticFeedback, session, hapticActionInfo);
}

//! OpenXR API function @ep{xrGetInputSourceLocalizedName}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetInputSourceLocalizedName(XrSession session,
                              const XrInputSourceLocalizedNameGetInfo *getInfo,
                              uint32_t bufferCapacityInput,
                              uint32_t *bufferCountOutput,
                              char *buffer){
    PASS_MIRAGE(GetInputSourceLocalizedName, session, getInfo, bufferCapacityInput, bufferCountOutput, buffer);
}

//! OpenXR API function @ep{xrCreateHandTrackerEXT}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateHandTrackerEXT(XrSession session,
                       const XrHandTrackerCreateInfoEXT *createInfo,
                       XrHandTrackerEXT *handTracker){
    PASS_MIRAGE(CreateHandTrackerEXT, session, createInfo, handTracker);
}

//! OpenXR API function @ep{xrDestroyHandTrackerEXT}
XRAPI_ATTR XrResult XRAPI_CALL
xrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker){
    PASS_MIRAGE(DestroyHandTrackerEXT, handTracker);
}

//! OpenXR API function @ep{xrLocateHandJointsEXT}
XRAPI_ATTR XrResult XRAPI_CALL
xrLocateHandJointsEXT(XrHandTrackerEXT handTracker,
                      const XrHandJointsLocateInfoEXT *locateInfo,
                      XrHandJointLocationsEXT *locations){
    PASS_MIRAGE(LocateHandJointsEXT, handTracker, locateInfo, locations);
}

//! OpenXR API function @ep{xrApplyForceFeedbackCurlMNDX}
XRAPI_ATTR XrResult XRAPI_CALL
xrApplyForceFeedbackCurlMNDX(XrHandTrackerEXT handTracker, const XrForceFeedbackCurlApplyLocationsMNDX *locations){
    PASS_MIRAGE(ApplyForceFeedbackCurlMNDX, handTracker, locations);
}

//! OpenXR API function @ep{xrEnumerateDisplayRefreshRatesFB}
XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateDisplayRefreshRatesFB(XrSession session,
                                 uint32_t displayRefreshRateCapacityInput,
                                 uint32_t *displayRefreshRateCountOutput,
                                 float *displayRefreshRates){
    PASS_MIRAGE(EnumerateDisplayRefreshRatesFB, session, displayRefreshRateCapacityInput, displayRefreshRateCountOutput, displayRefreshRates);
}

//! OpenXR API function @ep{xrGetDisplayRefreshRateFB}
XRAPI_ATTR XrResult XRAPI_CALL
xrGetDisplayRefreshRateFB(XrSession session, float *displayRefreshRate){
    PASS_MIRAGE(GetDisplayRefreshRateFB, session, displayRefreshRate);
}

//! OpenXR API function @ep{xrRequestDisplayRefreshRateFB}
XRAPI_ATTR XrResult XRAPI_CALL
xrRequestDisplayRefreshRateFB(XrSession session, float displayRefreshRate) {
    PASS_MIRAGE(RequestDisplayRefreshRateFB, session, displayRefreshRate);
}