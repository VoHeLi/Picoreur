#pragma once

#include <openxr/openxr_runtime.h>

#define LEFT_HAND 0
#define RIGHT_HAND 1

static XrSpace handSpaces[2];
static XrPath handPaths[2];
static const const char* handSpacesPathNames[2] = {"/user/hand/left", "/user/hand/right"};

void TryRegisterControllerPath(XrPath path, const char* pathStr);

void TryRegisterControllerSpace(XrSpace space, XrPath path);

void GetControllerSpacePose(XrSpace space, XrPosef* pose);