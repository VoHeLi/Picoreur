
#include "controllers_binding.h"
#include "handtracking_inputs.h"

#include <string>
#include <cmath>
#include <ctime>
#include <chrono>
#include <algorithm>

#include <android/log.h>

void TryRegisterControllerPath(XrPath path, const char* pathStr){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryRegisterControllerPath : %p, %s ", path, pathStr);
    if(strcmp(pathStr, handSpacesPathNames[LEFT_HAND]) == 0){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering left hand");
        handPaths[LEFT_HAND] = path;
    }
    else if(strcmp(pathStr, handSpacesPathNames[RIGHT_HAND]) == 0){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering right hand");
        handPaths[RIGHT_HAND] = path;
    }
    else if(strcmp(pathStr, "/interaction_profiles/bytedance/pico4_controller") == 0){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering interaction_profile : %p, %s ", path, pathStr);
        interactionProfilePath = path;
    }
    else{
        for(int i = 0; i < 33; i++){
            if(strcmp(pathStr, controllerPathNames[i]) == 0){
                __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering controller path : %d", i);
                controllerPaths[i] = path;
            }
        }
    }
}

void TryRegisterControllerSpace(XrSpace space, XrAction action, XrPath path){ //TODO GET ONLY INTERESTED POSE (ONLY GRIP AND PICO4)

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryRegisterControllerSpace : %p, %p, %p ", space, path, action);
    if(path == handPaths[LEFT_HAND]){ //Force grip pos and not pointer
        handSpaces[LEFT_HAND].push_back(space);
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering left hand : %p, %p, %p ", space, path, action);
    }
    else if(path == handPaths[RIGHT_HAND]) { //Force grip pos and not pointer
        handSpaces[RIGHT_HAND].push_back(space);
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering right hand : %p, %p, %p ", space, path, action);
    }
}

void GetControllerSpacePose(XrTime time, XrSpace space, XrSpace baseSpace, XrSpaceLocation *location){

    //DEBUG
    /*updateHandJoints(time, baseSpace, XR_HAND_LEFT_EXT);

    tryGetPalmPosition(XR_HAND_LEFT_EXT, &location->pose); //FOR NOW*/

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryGetControllerSpacePose : %p", space);

    //Update Hand Joints here
    if(std::find(handSpaces[LEFT_HAND].begin(), handSpaces[LEFT_HAND].end(), space) != handSpaces[LEFT_HAND].end()){
        updateHandJoints(time, baseSpace, XR_HAND_LEFT_EXT);
        tryGetBonePose(XR_HAND_LEFT_EXT, &location->pose, XR_HAND_JOINT_PALM_EXT); //FOR NOW
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryGetControllerSpacePose left : %p", space);
    }
    else if(std::find(handSpaces[RIGHT_HAND].begin(), handSpaces[RIGHT_HAND].end(), space) != handSpaces[RIGHT_HAND].end()){
        updateHandJoints(time, baseSpace, XR_HAND_RIGHT_EXT);
        tryGetBonePose(XR_HAND_RIGHT_EXT, &location->pose, XR_HAND_JOINT_PALM_EXT); //FOR NOW
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryGetControllerSpacePose right : %p", space);
    }
    else return;

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "GetControllerSpacePose : %p", space);
    location->locationFlags = XR_SPACE_LOCATION_POSITION_TRACKED_BIT | XR_SPACE_LOCATION_POSITION_VALID_BIT | XR_SPACE_LOCATION_ORIENTATION_VALID_BIT | XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT;

    //DEBUG
    /*float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    location->pose.position.x = r;*/
}

void TryRegisterActionSet(XrActionSet actionSet, const char* actionSetName){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Try Registering ActionSet : %p, %s ", actionSet, actionSetName);
    if(strcmp(actionSetName, controllersActionSetName) == 0){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering ActionSet : %p, %s ", actionSet, actionSetName);
        controllersActionSet = actionSet;
    }
}

void TryRegisterAction(XrAction action, XrActionSet actionSet, const char* actionName){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Try Registering Action : %p, %s, %p ", action, actionName, actionSet);

    if(actionSet != controllersActionSet) return;

    for(int i = 0; i < 17; i++){
        if(strcmp(actionName, controllersActionsNames[i]) == 0){
            __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Registering Action : %p, %s, %p ", action, actionName, actionSet);
            controllersActions[i] = action;
        }
    }
}

XrResult GetControllerDefaultBinding(const XrInteractionProfileSuggestedBinding *suggestedBindings){
    if(controllersActionSet == NULL){
        return XR_ERROR_PATH_UNSUPPORTED;
    }

    return XR_SUCCESS;
}

XrResult GetCurrentInteractionProfileBinding(XrInteractionProfileState *interactionProfile){
    if(interactionProfilePath != NULL){
        interactionProfile->interactionProfile = interactionProfilePath;
        return XR_SUCCESS;
    }

    return XR_ERROR_PATH_UNSUPPORTED;
}

//Get actions
void GetControllerActionStateBoolean(const XrActionStateGetInfo *getInfo, XrActionStateBoolean *data){
    XrHandEXT hand = getInfo->subactionPath == handPaths[LEFT_HAND] ? XR_HAND_LEFT_EXT : XR_HAND_RIGHT_EXT;

    uint32_t actionId = 0;
    for(int i = 0; i < 33; i++){
        if(getInfo->action == controllersActions[i]){
            actionId = i;
            break;
        }
    }

    switch(actionId){
        case TRIGGER_PRESSED:
            UpdateIfTriggerPressed(hand, data);
            break;
    }


    data->currentState = XR_TRUE;
}

//Controllers Binding

void UpdateIfTriggerPressed(XrHandEXT hand, XrActionStateBoolean *data){
    XrPosef palmPose;
    XrPosef indexTipPose;
    tryGetBonePose(hand, &palmPose, XR_HAND_JOINT_PALM_EXT);
    tryGetBonePose(hand, &indexTipPose, XR_HAND_JOINT_INDEX_TIP_EXT);
    //__android_log_print(ANDROID_LOG_DEBUG, "PICOEMU", "Getting poses : ");


}