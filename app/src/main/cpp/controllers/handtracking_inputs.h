#pragma once

#include <openxr/openxr_runtime.h>
#include "mirage_app/mirage_main.h"

static XrHandTrackerEXT leftHandTracker;
static XrHandTrackerEXT rightHandTracker;

static XrHandJointLocationEXT leftJointLocations[XR_HAND_JOINT_COUNT_EXT];
static XrHandJointLocationEXT rightJointLocations[XR_HAND_JOINT_COUNT_EXT];

void initializeHands(XrSession session);

void destroyHands();

void updateHandJoints(XrTime currentTime, XrSpace baseSpace, XrHandEXT handType);

XrResult tryGetPalmPosition(XrHandEXT handType, XrPosef* pose);