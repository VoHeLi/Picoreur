
#include <algorithm>
#include "mirage_main.h"

#include <android/log.h>
#include "platformplugin.h"

#include <string>
#include <vector>


void CreateInstanceInternal(const std::shared_ptr<IPlatformPlugin>& platformPlugin) {
    // Create union of extensions required by platform and graphics plugins.
    std::vector<const char*> extensions;/* = {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME, XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME};*/

    // Transform platform and graphics extension std::strings to C strings.
    const std::vector<std::string> platformExtensions = platformPlugin->GetInstanceExtensions();
    std::transform(platformExtensions.begin(), platformExtensions.end(), std::back_inserter(extensions),
                   [](const std::string& ext) { return ext.c_str(); });
    const std::vector<std::string> graphicsExtensions = {XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME};
    std::transform(graphicsExtensions.begin(), graphicsExtensions.end(), std::back_inserter(extensions),
                   [](const std::string& ext) { return ext.c_str(); });



    XrInstanceCreateInfo createInfo{XR_TYPE_INSTANCE_CREATE_INFO};
    createInfo.next = platformPlugin->GetInstanceCreateExtension();
    createInfo.enabledExtensionCount = (uint32_t)extensions.size();
    createInfo.enabledExtensionNames = extensions.data();

    strcpy(createInfo.applicationInfo.applicationName, "Picoreur Mirage");
    createInfo.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;

    //DEBUG XRINSTANCECREATEINFO :
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo type : %d", createInfo.type);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo createFlags : %p", createInfo.createFlags);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo applicationInfo : %p", createInfo.applicationInfo);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo enabledExtensionCount : %d", createInfo.enabledExtensionCount);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo enableApiLayerCount : %d", createInfo.enabledApiLayerCount);

    for(int i = 0; i < createInfo.enabledExtensionCount; i++){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xrCreateInstance createInfo enabled Extension : %s", createInfo.enabledExtensionNames[i]);
    }

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Before xrCreateInstance Mirage call");

    PFN_xrCreateInstance l_xrCreateInstance;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(nullptr, "xrCreateInstance", (PFN_xrVoidFunction*)&l_xrCreateInstance))){
        l_xrCreateInstance(&createInfo, &mirageInstance);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrCreateInstance not loaded from Lynx libopenxr_loader.so");
    }


}

void CreateInstance() {

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Starting Mirage Instance");
    CreateInstanceInternal(miragePlatformPlugin);
}

XrResult initializeMirageAppInstance(void* vm, void* clazz){

    miragePlatformPlugin = CreatePlatformPlugin(vm, clazz);

    //Initialize the loader
    PFN_xrInitializeLoaderKHR initializeLoader = nullptr;
    if (XR_SUCCEEDED(
            m_xrGetInstanceProcAddr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)(&initializeLoader)))) {
        XrLoaderInitInfoAndroidKHR loaderInitInfoAndroid = {XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR};
        loaderInitInfoAndroid.applicationVM = vm;
        loaderInitInfoAndroid.applicationContext = clazz;

        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : loaderInitInfoAndroid.applicationVM : %p", loaderInitInfoAndroid.applicationContext);
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : loaderInitInfoAndroid.applicationContext : %p", loaderInitInfoAndroid.applicationVM);

        initializeLoader((const XrLoaderInitInfoBaseHeaderKHR*)&loaderInitInfoAndroid);
    }

    CreateInstance();

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "Mirage Instance successfully created!");
    return XR_SUCCESS;
}

XrResult destroyMirageInstance(){
    PFN_xrDestroyInstance l_xrDestroyInstance;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrDestroyInstance", (PFN_xrVoidFunction *)&l_xrDestroyInstance))){
        return l_xrDestroyInstance(mirageInstance);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrDestroyInstance not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

//TODO : Control events
XrResult pollMirageEvents(XrEventDataBuffer *eventData){
    PFN_xrPollEvent l_xrPollEvent;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrPollEvent", (PFN_xrVoidFunction *)&l_xrPollEvent))){
        return l_xrPollEvent(mirageInstance, eventData);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrPollEvent not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

XrResult getMirageSystem(const XrSystemGetInfo* systemGetInfo, XrSystemId* systemId){
    PFN_xrGetSystem l_xrGetSystem;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrGetSystem", (PFN_xrVoidFunction *)&l_xrGetSystem))){
        return l_xrGetSystem(mirageInstance, systemGetInfo, systemId);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrGetSystem not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

XrResult getMirageSystemProperties(XrSystemId systemId, XrSystemProperties *properties){
    PFN_xrGetSystemProperties l_xrGetSystemProperties;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrGetSystemProperties", (PFN_xrVoidFunction *)&l_xrGetSystemProperties))){
        return l_xrGetSystemProperties(mirageInstance, systemId, properties);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrGetSystemProperties not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

XrResult mirageEnumerateViewConfigurations( XrSystemId systemId, uint32_t viewConfigurationTypeCapacityInput, uint32_t *viewConfigurationTypeCountOutput, XrViewConfigurationType *viewConfigurationTypes){
    PFN_xrEnumerateViewConfigurations l_xrEnumerateViewConfigurations;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrEnumerateViewConfigurations", (PFN_xrVoidFunction *)&l_xrEnumerateViewConfigurations))){
        return l_xrEnumerateViewConfigurations(mirageInstance, systemId, viewConfigurationTypeCapacityInput, viewConfigurationTypeCountOutput, viewConfigurationTypes);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrEnumerateViewConfigurations not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

XrResult mirageGetViewConfigurationProperties(XrSystemId systemId, XrViewConfigurationType viewConfigurationType, XrViewConfigurationProperties *configurationProperties){
    PFN_xrGetViewConfigurationProperties l_xrGetViewConfigurationProperties;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrGetViewConfigurationProperties", (PFN_xrVoidFunction *)&l_xrGetViewConfigurationProperties))){
        return l_xrGetViewConfigurationProperties(mirageInstance, systemId, viewConfigurationType, configurationProperties);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrGetViewConfigurationProperties not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

XrResult mirageEnumerateViewConfigurationViews(XrSystemId systemId,XrViewConfigurationType viewConfigurationType, uint32_t viewCapacityInput, uint32_t *viewCountOutput, XrViewConfigurationView *views){
    PFN_xrEnumerateViewConfigurationViews l_xrEnumerateViewConfigurationViews;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrEnumerateViewConfigurationViews", (PFN_xrVoidFunction *)&l_xrEnumerateViewConfigurationViews))){
        return l_xrEnumerateViewConfigurationViews(mirageInstance, systemId, viewConfigurationType, viewCapacityInput, viewCountOutput, views);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrEnumerateViewConfigurationViews not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}


XrResult mirageEnumerateEnvironmentBlendModes(XrSystemId systemId, XrViewConfigurationType viewConfigurationType, uint32_t environmentBlendModeCapacityInput,uint32_t *environmentBlendModeCountOutput,XrEnvironmentBlendMode *environmentBlendModes){
    PFN_xrEnumerateEnvironmentBlendModes l_xrEnumerateEnvironmentBlendModes;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrEnumerateEnvironmentBlendModes", (PFN_xrVoidFunction *)&l_xrEnumerateEnvironmentBlendModes))){
        return l_xrEnumerateEnvironmentBlendModes(mirageInstance, systemId, viewConfigurationType, environmentBlendModeCapacityInput, environmentBlendModeCountOutput, environmentBlendModes);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrEnumerateEnvironmentBlendModes not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

XrResult mirageGetOpenGLESGraphicsRequirementsKHR(XrSystemId systemId, XrGraphicsRequirementsOpenGLESKHR *graphicsRequirements){
    PFN_xrGetOpenGLESGraphicsRequirementsKHR l_xrGetOpenGLESGraphicsRequirementsKHR;
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, "xrGetOpenGLESGraphicsRequirementsKHR", (PFN_xrVoidFunction *)&l_xrGetOpenGLESGraphicsRequirementsKHR))){
        return l_xrGetOpenGLESGraphicsRequirementsKHR(mirageInstance, systemId, graphicsRequirements);
    }
    else{
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : xrGetOpenGLESGraphicsRequirementsKHR not loaded from Lynx libopenxr_loader.so");
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
}

#define MIRAGE_CALL(function, ...) PFN_##function l_##function; \
    if(XR_SUCCEEDED(m_xrGetInstanceProcAddr(mirageInstance, #function, (PFN_xrVoidFunction *)&l_##function))){ \
        return l_##function(__VA_ARGS__); \
    } \
    else{ \
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "Mirage : %s not loaded from Lynx libopenxr_loader.so", #function); \
        return XR_ERROR_FUNCTION_UNSUPPORTED; \
    } \

XrResult mirageCreateSession(const XrSessionCreateInfo *createInfo, XrSession *session){
    MIRAGE_CALL(xrCreateSession, mirageInstance, createInfo, session);
}

XrResult mirageDestroySession(XrSession session){
    MIRAGE_CALL(xrDestroySession, session);
}

XrResult mirageBeginSession(XrSession session, const XrSessionBeginInfo *beginInfo){
    MIRAGE_CALL(xrBeginSession, session, beginInfo);
}

XrResult mirageEndSession(XrSession session){
    MIRAGE_CALL(xrEndSession, session);
}

XrResult mirageWaitFrame(XrSession session, const XrFrameWaitInfo *frameWaitInfo, XrFrameState *frameState){
    MIRAGE_CALL(xrWaitFrame, session, frameWaitInfo, frameState);
}

XrResult mirageBeginFrame(XrSession session, const XrFrameBeginInfo *frameBeginInfo){
    MIRAGE_CALL(xrBeginFrame, session, frameBeginInfo);
}

XrResult mirageEndFrame(XrSession session, const XrFrameEndInfo *frameEndInfo){
    MIRAGE_CALL(xrEndFrame, session, frameEndInfo);
}

XrResult mirageRequestExitSession(XrSession session){
    MIRAGE_CALL(xrRequestExitSession, session);
}

XrResult mirageLocateViews(XrSession session, const XrViewLocateInfo *viewLocateInfo, XrViewState *viewState, uint32_t viewCapacityInput, uint32_t *viewCountOutput, XrView *views){
    MIRAGE_CALL(xrLocateViews, session, viewLocateInfo, viewState, viewCapacityInput, viewCountOutput, views);
}

XrResult mirageEnumerateReferenceSpaces(XrSession session, //PASS TODO : maybe change reference space to stage?
                                        uint32_t spaceCapacityInput,
                                        uint32_t *spaceCountOutput,
                                        XrReferenceSpaceType *spaces){
    MIRAGE_CALL(xrEnumerateReferenceSpaces, session, spaceCapacityInput, spaceCountOutput, spaces)
}

XrResult mirageGetReferenceSpaceBoundsRect(XrSession session, XrReferenceSpaceType referenceSpaceType, XrExtent2Df *bounds){
    MIRAGE_CALL(xrGetReferenceSpaceBoundsRect, session, referenceSpaceType, bounds)
}

XrResult mirageCreateReferenceSpace(XrSession session, const XrReferenceSpaceCreateInfo *createInfo, XrSpace *space){
    MIRAGE_CALL(xrCreateReferenceSpace, session, createInfo, space)
}

XrResult mirageLocateSpace(XrSpace space, XrSpace baseSpace, XrTime time, XrSpaceLocation *location){
    MIRAGE_CALL(xrLocateSpace, space, baseSpace, time, location)
}

XrResult mirageDestroySpace(XrSpace space){
    MIRAGE_CALL(xrDestroySpace, space)
}

XrResult mirageCreateActionSpace(XrSession session, const XrActionSpaceCreateInfo *createInfo, XrSpace *space){
    MIRAGE_CALL(xrCreateActionSpace, session, createInfo, space)
}



XrResult mirageCreateActionSet(const XrActionSetCreateInfo *createInfo, XrActionSet *actionSet) {
    MIRAGE_CALL(xrCreateActionSet, mirageInstance, createInfo, actionSet);
}

XrResult mirageDestroyActionSet(XrActionSet actionSet) {
    MIRAGE_CALL(xrDestroyActionSet, actionSet);
}

XrResult mirageCreateAction(XrActionSet actionSet, const XrActionCreateInfo *createInfo, XrAction *action) {
    MIRAGE_CALL(xrCreateAction, actionSet, createInfo, action);
}

XrResult mirageDestroyAction(XrAction action) {
    MIRAGE_CALL(xrDestroyAction, action);
}

XrResult mirageSuggestInteractionProfileBindings(const XrInteractionProfileSuggestedBinding *suggestedBindings) {
    MIRAGE_CALL(xrSuggestInteractionProfileBindings, mirageInstance, suggestedBindings);
}

XrResult mirageAttachSessionActionSets(XrSession session, const XrSessionActionSetsAttachInfo *bindInfo) {
    MIRAGE_CALL(xrAttachSessionActionSets, session, bindInfo);
}

XrResult mirageGetCurrentInteractionProfile(XrSession session, XrPath topLevelUserPath, XrInteractionProfileState *interactionProfile) {
    MIRAGE_CALL(xrGetCurrentInteractionProfile, session, topLevelUserPath, interactionProfile);
}

XrResult mirageGetActionStateBoolean(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateBoolean *data) {
    MIRAGE_CALL(xrGetActionStateBoolean, session, getInfo, data);
}

XrResult mirageGetActionStateFloat(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateFloat *data) {
    MIRAGE_CALL(xrGetActionStateFloat, session, getInfo, data);
}

XrResult mirageGetActionStateVector2f(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStateVector2f *data) {
    MIRAGE_CALL(xrGetActionStateVector2f, session, getInfo, data);
}

XrResult mirageGetActionStatePose(XrSession session, const XrActionStateGetInfo *getInfo, XrActionStatePose *data) {
    MIRAGE_CALL(xrGetActionStatePose, session, getInfo, data);
}

XrResult mirageSyncActions(XrSession session, const XrActionsSyncInfo *syncInfo) {
    MIRAGE_CALL(xrSyncActions, session, syncInfo);
}

XrResult mirageEnumerateBoundSourcesForAction(XrSession session, const XrBoundSourcesForActionEnumerateInfo *enumerateInfo,
                                          uint32_t sourceCapacityInput, uint32_t *sourceCountOutput, XrPath *sources) {
    MIRAGE_CALL(xrEnumerateBoundSourcesForAction, session, enumerateInfo, sourceCapacityInput, sourceCountOutput, sources);
}

XrResult mirageGetInputSourceLocalizedName(XrSession session, const XrInputSourceLocalizedNameGetInfo *getInfo,
                                       uint32_t bufferCapacityInput, uint32_t *bufferCountOutput, char *buffer) {
    MIRAGE_CALL(xrGetInputSourceLocalizedName, session, getInfo, bufferCapacityInput, bufferCountOutput, buffer);
}

XrResult mirageApplyHapticFeedback(XrSession session, const XrHapticActionInfo *hapticActionInfo, const XrHapticBaseHeader *hapticEvent) {
    MIRAGE_CALL(xrApplyHapticFeedback, session, hapticActionInfo, hapticEvent);
}

XrResult mirageStopHapticFeedback(XrSession session, const XrHapticActionInfo *hapticActionInfo) {
    MIRAGE_CALL(xrStopHapticFeedback, session, hapticActionInfo);
}

XrResult mirageCreateHandTrackerEXT(XrSession session, const XrHandTrackerCreateInfoEXT *createInfo, XrHandTrackerEXT *handTracker) {
    MIRAGE_CALL(xrCreateHandTrackerEXT, session, createInfo, handTracker);
}

XrResult mirageDestroyHandTrackerEXT(XrHandTrackerEXT handTracker) {
    MIRAGE_CALL(xrDestroyHandTrackerEXT, handTracker);
}

XrResult mirageLocateHandJointsEXT(XrHandTrackerEXT handTracker, const XrHandJointsLocateInfoEXT *locateInfo,
                               XrHandJointLocationsEXT *locations) {
    MIRAGE_CALL(xrLocateHandJointsEXT, handTracker, locateInfo, locations);
}

XrResult mirageApplyForceFeedbackCurlMNDX(XrHandTrackerEXT handTracker, const XrForceFeedbackCurlApplyLocationsMNDX *locations) {
    MIRAGE_CALL(xrApplyForceFeedbackCurlMNDX, handTracker, locations);
}

XrResult mirageEnumerateDisplayRefreshRatesFB(XrSession session, uint32_t displayRefreshRateCapacityInput,
                                          uint32_t *displayRefreshRateCountOutput, float *displayRefreshRates) {
    MIRAGE_CALL(xrEnumerateDisplayRefreshRatesFB, session, displayRefreshRateCapacityInput, displayRefreshRateCountOutput, displayRefreshRates);
}

XrResult mirageGetDisplayRefreshRateFB(XrSession session, float *displayRefreshRate) {
    MIRAGE_CALL(xrGetDisplayRefreshRateFB, session, displayRefreshRate);
}

XrResult mirageRequestDisplayRefreshRateFB(XrSession session, float displayRefreshRate) {
    MIRAGE_CALL(xrRequestDisplayRefreshRateFB, session, displayRefreshRate);
}