
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

    /*switch(actionId){
        case TRIGGER_PRESSED:
            UpdateIfTriggerPressed(hand, data);
            break;
    }*/
    UpdateIfTriggerPressed(hand, data);

    data->changedSinceLastSync = XR_TRUE;
    data->lastChangeTime = getCurrentTime();
    data->isActive = XR_TRUE;
}



//Controllers Binding
bool lastActive = false; //TODO
void UpdateIfTriggerPressed(XrHandEXT hand, XrActionStateBoolean *data){
    XrPosef palmPose;
    XrPosef indexTipPose;
    tryGetBonePose(hand, &palmPose, XR_HAND_JOINT_PALM_EXT);
    tryGetBonePose(hand, &indexTipPose, XR_HAND_JOINT_INDEX_DISTAL_EXT);
    //__android_log_print(ANDROID_LOG_DEBUG, "PICOEMU", "Getting poses : ");

    glm::vec3 palmGlobalPosition = glm::vec3(palmPose.position.x, palmPose.position.y, palmPose.position.z);//GLM_POS(palmPose);
    glm::vec3 indexGlobalPosition = glm::vec3(indexTipPose.position.x, indexTipPose.position.y, indexTipPose.position.z);//GLM_POS(indexTipPose);

    //glm::quat palmRot = glm::quat(palmPose.orientation.w, palmPose.orientation.x, palmPose.orientation.y, palmPose.orientation.z);//GLM_QUAT(palmPose);

    //glm::vec3 indexLocalPos = inverse(palmRot) * (indexGlobalPosition - palmGlobalPosition);

    float distSquare = (palmPose.position.x - indexTipPose.position.x)*(palmPose.position.x - indexTipPose.position.x)
                     + (palmPose.position.y - indexTipPose.position.y)*(palmPose.position.y - indexTipPose.position.y)
                     + (palmPose.position.z - indexTipPose.position.z)*(palmPose.position.z - indexTipPose.position.z);

    bool isActive = distSquare <= 0.005f;//0.03f*0.03f; //TODO CHANGE VALUE

    bool changedActive = lastActive != isActive;
    lastActive = isActive;

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Hand %d : Distance between palm and index : %.6f, palmGlobalPos : %.6f,%.6f,%.6f , indexTipGlobalPos : %.6f,%.6f,%.6f , isActive %d, isChanged %d ", hand, distSquare,
                        indexTipPose.position.x, indexTipPose.position.y, indexTipPose.position.z, indexTipPose.position.x, indexTipPose.position.y, indexTipPose.position.z, isActive, changedActive);



    data->currentState = isActive;
    data->changedSinceLastSync = XR_TRUE;
}