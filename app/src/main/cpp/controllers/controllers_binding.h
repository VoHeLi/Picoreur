#pragma once

#include <openxr/openxr_runtime.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/normal.hpp>

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

#include <vector>

#define LEFT_HAND 0
#define RIGHT_HAND 1

static std::vector<XrSpace> handSpaces[2];
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
static const const char* controllersActionSetName = "pico4touchcontroller"; // other  piconeo3controller


#define GRIP 0
#define GRIP_PRESSED 1
#define PRIMARY_BUTTON 2
#define PRIMARY_TOUCHED 3
#define SECONDARY_BUTTON 4
#define SECONDARY_TOUCHED 5
#define MENU 6
#define SYSTEM 7
#define TRIGGER 8
#define TRIGGER_PRESSED 9
#define TRIGGER_TOUCHED 10
#define THUMBSTICK 11
#define THUMBSTICK_CLICKED 12
#define THUMBSTICK_TOUCHED 13
#define DEVICE_POSE 14
#define POINTER 15
#define HAPTIC 16
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

void TryRegisterAction(XrAction action, XrActionSet actionSet, const char* actionName);

void GetControllerSpacePose(XrTime time, XrSpace space, XrSpace baseSpace, XrSpaceLocation *location);

XrResult GetControllerDefaultBinding(const XrInteractionProfileSuggestedBinding *suggestedBindings);

XrResult GetCurrentInteractionProfileBinding(XrInteractionProfileState *interactionProfile);

//Get actions

void GetControllerActionStateBoolean(const XrActionStateGetInfo *getInfo, XrActionStateBoolean *data);
void GetControllerActionStateFloat(const XrActionStateGetInfo *getInfo, XrActionStateFloat *data);
void GetControllerActionStateVector2f(const XrActionStateGetInfo *getInfo, XrActionStateVector2f *data);

// Controllers Binding
#define GLM_POS(pose) glm::vec3(##pose##.position.x, ##pose##.position.y, ##pose##.position.z)
#define GLM_QUAT(pose) glm::quat(##pose##.orientation.w, ##pose##.orientation.x, ##pose##.orientation.y, ##pose##.orientation.z)

void UpdateIfTriggerPressed(XrHandEXT hand, XrActionStateBoolean *data);
void UpdateIfGripPressed(XrHandEXT hand, XrActionStateBoolean *data);

void UpdateIfPrimaryButtonPressed(XrHandEXT hand, XrActionStateBoolean *data);

#define SECONDARY_BUTTON_LOC glm::vec3(0.124675, -0.224141, -0.119549)
#define SECONDARY_BUTTON_DISTANCE 0.02f
void UpdateIfSecondaryButtonPressed(XrHandEXT hand, XrActionStateBoolean *data);


#define THUMBSTICK_MIDDLE glm::vec3(0.029615,-0.056456,-0.024166)
#define THUMBSTICK_UP glm::vec3(0.019883,-0.063061,-0.028699)
#define THUMBSTICK_DOWN glm::vec3(0.047657,-0.043240,-0.013707)
#define THUMBSTICK_LEFT glm::vec3(0.024933, -0.038147, -0.033840) //(0.024933, -0.038147, -0.033840) glm::vec3(-0.043221,-0.055522,-0.028632)
#define THUMBSTICK_RIGHT glm::vec3(0.011134, -0.069010, -0.023969) // (0.011134, -0.069010, -0.023969) glm::vec3(0.008095,-0.071079,-0.026443)

void UpdateJoystickInput(XrHandEXT hand, XrActionStateVector2f* data); //THUMB DISTAL : 0.124675, -0.224141, -0.119549

void UpdateIfTriggerTouched(XrHandEXT hand, XrActionStateBoolean *data);

void UpdateIfGripTouched(XrHandEXT hand, XrActionStateFloat* data);

void UpdateIfJoystickTouched(XrHandEXT hand, XrActionStateBoolean *data);