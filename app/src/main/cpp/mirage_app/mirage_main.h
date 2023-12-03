#pragma once

#include <openxr/openxr_runtime.h>
#include <openxr/openxr_platform.h>
#include "mirage_loader.h"


static std::shared_ptr<IPlatformPlugin> miragePlatformPlugin;
static XrInstance mirageInstance;

XrResult initializeMirageAppInstance(void* vm, void* clazz);

XrResult destroyMirageInstance();

XrResult pollMirageEvents(XrEventDataBuffer *eventData);

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



