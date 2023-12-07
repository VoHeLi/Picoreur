#pragma once

#include <openxr/openxr_runtime.h>

#define USER_HAND_LEFT_INPUT_SQUEEZE_VALUE 0
#define USER_HAND_RIGHT_INPUT_SQUEEZE_VALUE 1
#define USER_HAND_LEFT_INPUT_SQUEEZE_CLICK 2
#define USER_HAND_RIGHT_INPUT_SQUEEZE_CLICK 3
#define USER_HAND_LEFT_INPUT_X_CLICK 4
#define USER_HAND_RIGHT_INPUT_A_CLICK 5
#define USER_HAND_LEFT_INPUT_X_TOUCH 6
#define USER_HAND_RIGHT_INPUT_A_TOUCH 7
#define USER_HAND_LEFT_INPUT_Y_CLICK 8
#define USER_HAND_RIGHT_INPUT_B_CLICK 9
#define USER_HAND_LEFT_INPUT_Y_TOUCH 10
#define USER_HAND_RIGHT_INPUT_B_TOUCH 11
#define USER_HAND_LEFT_INPUT_MENU_CLICK 12
#define USER_HAND_LEFT_INPUT_SYSTEM_CLICK 13
#define USER_HAND_RIGHT_INPUT_SYSTEM_CLICK 14
#define USER_HAND_LEFT_INPUT_TRIGGER_VALUE 15
#define USER_HAND_RIGHT_INPUT_TRIGGER_VALUE 16
#define USER_HAND_LEFT_INPUT_TRIGGER_CLICK 17
#define USER_HAND_RIGHT_INPUT_TRIGGER_CLICK 18
#define USER_HAND_LEFT_INPUT_TRIGGER_TOUCH 19
#define USER_HAND_RIGHT_INPUT_TRIGGER_TOUCH 20
#define USER_HAND_LEFT_INPUT_THUMBSTICK 21
#define USER_HAND_RIGHT_INPUT_THUMBSTICK 22
#define USER_HAND_LEFT_INPUT_THUMBSTICK_CLICK 23
#define USER_HAND_RIGHT_INPUT_THUMBSTICK_CLICK 24
#define USER_HAND_LEFT_INPUT_THUMBSTICK_TOUCH 25
#define USER_HAND_RIGHT_INPUT_THUMBSTICK_TOUCH 26
#define USER_HAND_LEFT_INPUT_GRIP_POSE 27
#define USER_HAND_RIGHT_INPUT_GRIP_POSE 28
#define USER_HAND_LEFT_INPUT_AIM_POSE 29
#define USER_HAND_RIGHT_INPUT_AIM_POSE 30
#define USER_HAND_LEFT_OUTPUT_HAPTIC 31
#define USER_HAND_RIGHT_OUTPUT_HAPTIC 32

#define LEFT_HAND 0
#define RIGHT_HAND 1

static XrSpace handSpaces[2];
static XrPath handPaths[2];
static const const char* handSpacesPathNames[2] = {"/user/hand/left", "/user/hand/right"};

static XrPath interactionProfilePath;
static XrPath controllerPaths[33];
static const const char* controllerPathNames[33] = {
        "/user/hand/left/input/squeeze/value",
        "/user/hand/right/input/squeeze/value",
        "/user/hand/left/input/squeeze/click",
        "/user/hand/right/input/squeeze/click",
        "/user/hand/left/input/x/click",
        "/user/hand/right/input/a/click",
        "/user/hand/left/input/x/touch",
        "/user/hand/right/input/a/touch",
        "/user/hand/left/input/y/click",
        "/user/hand/right/input/b/click",
        "/user/hand/left/input/y/touch",
        "/user/hand/right/input/b/touch",
        "/user/hand/left/input/menu/click",
        "/user/hand/left/input/system/click",
        "/user/hand/right/input/system/click",
        "/user/hand/left/input/trigger/value",
        "/user/hand/right/input/trigger/value",
        "/user/hand/left/input/trigger/click",
        "/user/hand/right/input/trigger/click",
        "/user/hand/left/input/trigger/touch",
        "/user/hand/right/input/trigger/touch",
        "/user/hand/left/input/thumbstick",
        "/user/hand/right/input/thumbstick",
        "/user/hand/left/input/thumbstick/click",
        "/user/hand/right/input/thumbstick/click",
        "/user/hand/left/input/thumbstick/touch",
        "/user/hand/right/input/thumbstick/touch",
        "/user/hand/left/input/grip/pose",
        "/user/hand/right/input/grip/pose",
        "/user/hand/left/input/aim/pose",
        "/user/hand/right/input/aim/pose",
        "/user/hand/left/output/haptic",
        "/user/hand/right/output/haptic"
};

static XrActionSet controllersActionSet;
static const const char* controllersActionSetName = "pico4touchcontroller";


//TODO DEFINE ACTIONS
#define XR_ACTION_DEVICE_POSE 14
static XrAction controllersActions[17];
static const const char* controllersActionsNames[17] = {
        "grip", "grippressed", "primarybutton", "primarytouched",
        "secondarybutton", "secondarytouched", "menu", "system",
        "trigger", "triggerpressed", "triggertouched", "thumbstick",
        "thumbstickclicked", "thumbsticktouched", "devicepose", "pointer", "haptic"
};


void TryRegisterControllerPath(XrPath path, const char* pathStr);

void TryRegisterControllerSpace(XrSpace space, XrAction action, XrPath path);

void TryRegisterActionSet(XrActionSet actionSet, const char* actionSetName);

void TryRegisterAction(XrAction action, const char* actionName);

void GetControllerSpacePose(XrTime time, XrSpace space, XrSpaceLocation *location);

XrResult GetControllerDefaultBinding(const XrInteractionProfileSuggestedBinding *suggestedBindings);

XrResult GetCurrentInteractionProfileBinding(XrInteractionProfileState *interactionProfile);
