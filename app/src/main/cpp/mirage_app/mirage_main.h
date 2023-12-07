#pragma once

#include <openxr/openxr_runtime.h>
#include <openxr/openxr_platform.h>
#include "mirage_loader.h"

#define MIRAGE_CALL(function, ...) PFN_##function l_##function; \
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, #function, (PFN_xrVoidFunction *)&l_##function))){ \
        return l_##function(__VA_ARGS__); \
    } \
    else{ \
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : %s not loaded from Lynx libopenxr_loader.so", #function); \
        return XR_ERROR_FUNCTION_UNSUPPORTED; \
    } \

static std::shared_ptr<IPlatformPlugin> miragePlatformPlugin;
static XrInstance mirageInstance;
static XrSession mirageSession;


XrResult initializeMirageAppInstance(void* vm, void* clazz);

XrResult destroyMirageInstance();

XrResult pollMirageEvents(XrEventDataBuffer *eventData);


XrResult miragePathToString(XrPath path, uint32_t bufferCapacityInput, uint32_t *bufferCountOutput, char *buffer);

XrResult mirageStringToPath(const char *pathString, XrPath *out_path);




XrResult getMirageSystem(const XrSystemGetInfo* systemGetInfo, XrSystemId* systemId);

XrResult getMirageSystemProperties(XrSystemId systemId, XrSystemProperties *properties);

XrResult mirageEnumerateViewConfigurations( XrSystemId systemId, uint32_t viewConfigurationTypeCapacityInput, uint32_t *viewConfigurationTypeCountOutput, XrViewConfigurationType *viewConfigurationTypes);

XrResult mirageGetViewConfigurationProperties(XrSystemId systemId, XrViewConfigurationType viewConfigurationType, XrViewConfigurationProperties *configurationProperties);

XrResult mirageEnumerateViewConfigurationViews(XrSystemId systemId,XrViewConfigurationType viewConfigurationType, uint32_t viewCapacityInput, uint32_t *viewCountOutput, XrViewConfigurationView *views);

XrResult mirageEnumerateEnvironmentBlendModes(XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t environmentBlendModeCapacityInput,uint32_t *environmentBlendModeCountOutput,XrEnvironmentBlendMode *environmentBlendModes);

XrResult mirageGetOpenGLESGraphicsRequirementsKHR(XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR *graphicsRequirements);


XrResult mirageCreateSession(const XrSessionCreateInfo *createInfo, XrSession *session);

XrResult mirageDestroySession(XrSession session);

XrResult mirageBeginSession(XrSession session, const XrSessionBeginInfo *beginInfo);

XrResult mirageEndSession(XrSession session);

XrResult mirageWaitFrame(XrSession session, const XrFrameWaitInfo *frameWaitInfo, XrFrameState *frameState);

XrResult mirageBeginFrame(XrSession session, const XrFrameBeginInfo *frameBeginInfo);

XrResult mirageEndFrame(XrSession session, const XrFrameEndInfo *frameEndInfo);

XrResult mirageRequestExitSession(XrSession session);

XrResult mirageLocateViews(XrSession session, const XrViewLocateInfo *viewLocateInfo, XrViewState *viewState, uint32_t viewCapacityInput, uint32_t *viewCountOutput, XrView *views);


XrResult mirageEnumerateReferenceSpaces(XrSession session, //PASS TODO : maybe change reference space to stage?
                           uint32_t spaceCapacityInput,
                           uint32_t *spaceCountOutput,
                           XrReferenceSpaceType *spaces);

XrResult mirageGetReferenceSpaceBoundsRect(XrSession session, XrReferenceSpaceType referenceSpaceType, XrExtent2Df *bounds);

XrResult mirageCreateReferenceSpace(XrSession session, const XrReferenceSpaceCreateInfo *createInfo, XrSpace *space);

XrResult mirageLocateSpace(XrSpace space, XrSpace baseSpace, XrTime time, XrSpaceLocation *location);

XrResult mirageDestroySpace(XrSpace space);

XrResult mirageCreateActionSpace(XrSession session, const XrActionSpaceCreateInfo *createInfo, XrSpace *space);


//ACTIONS

XrResult mirageCreateActionSet(const XrActionSetCreateInfo *createInfo, XrActionSet *actionSet);

XrResult mirageDestroyActionSet(XrActionSet actionSet);

XrResult mirageCreateAction(XrActionSet actionSet, const XrActionCreateInfo *createInfo, XrAction *action);

XrResult mirageDestroyAction(XrAction action);

XrResult mirageSuggestInteractionProfileBindings(const XrInteractionProfileSuggestedBinding *suggestedBindings);

XrResult mirageAttachSessionActionSets(XrSession session, const XrSessionActionSetsAttachInfo *bindInfo);

XrResult mirageGetCurrentInteractionProfile(XrSession session, XrPath topLevelUserPath, XrInteractionProfileState *interactionProfile);

XrResult mirageGetActionStateBoolean(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateBoolean *data);

XrResult mirageGetActionStateFloat(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateFloat *data);

XrResult mirageGetActionStateVector2f(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateVector2f *data);

XrResult mirageGetActionStatePose(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStatePose *data);

XrResult mirageSyncActions(XrSession session, const XrActionsSyncInfo *syncInfo);

XrResult mirageEnumerateBoundSourcesForAction(XrSession session, const XrBoundSourcesForActionEnumerateInfo *enumerateInfo,
                                          uint32_t sourceCapacityInput, uint32_t *sourceCountOutput, XrPath *sources);

XrResult mirageGetInputSourceLocalizedName(XrSession session, const XrInputSourceLocalizedNameGetInfo *getInfo,
                                       uint32_t bufferCapacityInput, uint32_t *bufferCountOutput, char *buffer);

XrResult mirageApplyHapticFeedback(XrSession session, const XrHapticActionInfo *hapticActionInfo, const XrHapticBaseHeader *hapticEvent);

XrResult mirageStopHapticFeedback(XrSession session, const XrHapticActionInfo *hapticActionInfo);

XrResult mirageCreateHandTrackerEXT(XrSession session, const XrHandTrackerCreateInfoEXT *createInfo, XrHandTrackerEXT *handTracker);

XrResult mirageDestroyHandTrackerEXT(XrHandTrackerEXT handTracker);

XrResult mirageLocateHandJointsEXT(XrHandTrackerEXT handTracker, const XrHandJointsLocateInfoEXT *locateInfo, XrHandJointLocationsEXT *locations);

XrResult mirageApplyForceFeedbackCurlMNDX(XrHandTrackerEXT handTracker, const XrForceFeedbackCurlApplyLocationsMNDX *locations);

XrResult mirageEnumerateDisplayRefreshRatesFB(XrSession session, uint32_t displayRefreshRateCapacityInput,
                                          uint32_t *displayRefreshRateCountOutput, float *displayRefreshRates);

XrResult mirageGetDisplayRefreshRateFB(XrSession session, float *displayRefreshRate);

XrResult mirageRequestDisplayRefreshRateFB(XrSession session, float displayRefreshRate);


XrResult mirageEnumerateSwapchainFormats(XrSession session, uint32_t formatCapacityInput, uint32_t *formatCountOutput, int64_t *formats);

XrResult mirageCreateSwapchain(XrSession session, const XrSwapchainCreateInfo *createInfo, XrSwapchain *swapchain);

XrResult mirageDestroySwapchain(XrSwapchain swapchain);

XrResult mirageEnumerateSwapchainImages(XrSwapchain swapchain, uint32_t imageCapacityInput, uint32_t *imageCountOutput, XrSwapchainImageBaseHeader *images);

XrResult mirageAcquireSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageAcquireInfo *acquireInfo, uint32_t *index);

XrResult mirageWaitSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageWaitInfo *waitInfo);

XrResult mirageReleaseSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageReleaseInfo *releaseInfo);


//DEBUG EXT


XrResult mirageSetDebugUtilsObjectNameEXT(const XrDebugUtilsObjectNameInfoEXT *nameInfo);

XrResult mirageCreateDebugUtilsMessengerEXT(
                               const XrDebugUtilsMessengerCreateInfoEXT *createInfo,
                               XrDebugUtilsMessengerEXT *messenger);
XrResult mirageDestroyDebugUtilsMessengerEXT(XrDebugUtilsMessengerEXT messenger);

XrResult mirageSubmitDebugUtilsMessageEXT(
                             XrDebugUtilsMessageSeverityFlagsEXT messageSeverity,
                             XrDebugUtilsMessageTypeFlagsEXT messageTypes,
                             const XrDebugUtilsMessengerCallbackDataEXT *callbackData);

XrResult mirageSessionBeginDebugUtilsLabelRegionEXT(XrSession session, const XrDebugUtilsLabelEXT *labelInfo);

XrResult mirageSessionEndDebugUtilsLabelRegionEXT(XrSession session);

XrResult mirageSessionInsertDebugUtilsLabelEXT(XrSession session, const XrDebugUtilsLabelEXT *labelInfo);


XrResult mirageCreateHandTrackerEXT(XrSession session, const XrHandTrackerCreateInfoEXT *createInfo,
                                    XrHandTrackerEXT *handTracker);

XrResult mirageDestroyHandTrackerEXT(XrHandTrackerEXT handTracker);

XrResult mirageLocateHandJointsEXT(XrHandTrackerEXT handTracker,
                                   const XrHandJointsLocateInfoEXT *locateInfo,
                                   XrHandJointLocationsEXT *locations);