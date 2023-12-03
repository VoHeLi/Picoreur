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

