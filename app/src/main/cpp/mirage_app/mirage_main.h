#pragma once

#include <openxr/openxr_runtime.h>
#include <openxr/openxr_platform.h>
#include "mirage_loader.h"


static std::shared_ptr<IPlatformPlugin> miragePlatformPlugin;
static XrInstance mirageInstance;

XrResult initializeMirageAppInstance(void* vm, void* clazz);

XrResult destroyMirageInstance();

XrResult pollMirageEvents(XrEventDataBuffer *eventData);
