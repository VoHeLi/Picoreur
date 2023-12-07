#pragma once

#include <openxr/openxr_runtime.h>
#include "mirage_app/mirage_main.h"

static XrHandTrackerEXT leftHandTracker;
static XrHandTrackerEXT rightHandTracker;

static XrHandJointLocationsEXT leftJointLocations;
static XrHandJointLocationsEXT rightJointLocations;

void initializeHands(XrSession session);

void destroyHands();

void updateHandJoints(XrTime currentTime, XrSpace currentSpace, XrHandEXT handType);

XrResult tryGetPalmPosition(XrHandEXT handType, XrPosef* pose);