
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

        //We rotate the hand correctly

        XrPosef palmPose;
        tryGetBonePose(XR_HAND_LEFT_EXT, &palmPose, XR_HAND_JOINT_PALM_EXT); //FOR NOW
        glm::quat palmRot = glm::quat(palmPose.orientation.w, palmPose.orientation.x, palmPose.orientation.y, palmPose.orientation.z);
        glm::quat finalRot = palmRot * glm::angleAxis(1.5707963268f, glm::vec3(0.0f,0.0f,-1.0f));
        XrQuaternionf xrFinalRot = XrQuaternionf{
            .w = finalRot.w,
            .x = finalRot.x,
            .y = finalRot.y,
            .z = finalRot.z
        };

        location->pose.position = palmPose.position;
        location->pose.orientation = xrFinalRot;

        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryGetControllerSpacePose left : %p", space);
    }
    else if(std::find(handSpaces[RIGHT_HAND].begin(), handSpaces[RIGHT_HAND].end(), space) != handSpaces[RIGHT_HAND].end()){
        updateHandJoints(time, baseSpace, XR_HAND_RIGHT_EXT);
        XrPosef palmPose;


        tryGetBonePose(XR_HAND_RIGHT_EXT, &palmPose, XR_HAND_JOINT_PALM_EXT); //FOR NOW
        glm::quat palmRot = glm::quat(palmPose.orientation.w, palmPose.orientation.x, palmPose.orientation.y, palmPose.orientation.z);
        glm::quat finalRot = palmRot * glm::angleAxis(1.5707963268f, glm::vec3(0.0f,0.0f,1.0f));
        XrQuaternionf xrFinalRot = XrQuaternionf{
                .w = finalRot.w,
                .x = finalRot.x,
                .y = finalRot.y,
                .z = finalRot.z
        };

        location->pose.position = palmPose.position;
        location->pose.orientation = xrFinalRot;


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
        case PRIMARY_BUTTON:
            UpdateIfPrimaryButtonPressed(hand, data);
            break;
        case SECONDARY_BUTTON:
            UpdateIfSecondaryButtonPressed(hand, data);
            break;
    }
    //UpdateIfTriggerPressed(hand, data);

    data->changedSinceLastSync = XR_TRUE;
    data->lastChangeTime = getCurrentTime();
    data->isActive = XR_TRUE;
}

void GetControllerActionStateVector2f(const XrActionStateGetInfo *getInfo, XrActionStateVector2f *data){
    XrHandEXT hand = getInfo->subactionPath == handPaths[LEFT_HAND] ? XR_HAND_LEFT_EXT : XR_HAND_RIGHT_EXT;

    uint32_t actionId = 0;
    for(int i = 0; i < 33; i++){
        if(getInfo->action == controllersActions[i]){
            actionId = i;
            break;
        }
    }

    switch(actionId){
        case THUMBSTICK:
            UpdateJoystickInput(hand, data);
            break;
    }
    //UpdateIfTriggerPressed(hand, data);

    data->changedSinceLastSync = XR_TRUE;
    data->lastChangeTime = getCurrentTime();
    data->isActive = XR_TRUE;
}



//Controllers Binding
bool triggerLeftLastState = false;
bool triggerRightLastState = false;
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

    if(hand == XR_HAND_LEFT_EXT){
        bool changedActive = triggerLeftLastState != isActive;
        triggerLeftLastState = isActive;
        data->changedSinceLastSync = changedActive;
    }
    else{
        bool changedActive = triggerRightLastState != isActive;
        triggerRightLastState = isActive;
        data->changedSinceLastSync = changedActive;
    }


    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Hand %d : Distance between palm and index : %.6f, palmGlobalPos : %.6f,%.6f,%.6f , indexTipGlobalPos : %.6f,%.6f,%.6f , isActive %d ", hand, distSquare,
                        indexTipPose.position.x, indexTipPose.position.y, indexTipPose.position.z, indexTipPose.position.x, indexTipPose.position.y, indexTipPose.position.z, isActive);


    data->currentState = isActive;

}

bool primaryLeftLastState = false;
bool primaryRightLastState = false;
void UpdateIfPrimaryButtonPressed(XrHandEXT hand, XrActionStateBoolean *data){
    XrPosef thumbDistalPos;
    XrPosef indexProximalPose;
    tryGetBonePose(hand, &thumbDistalPos, XR_HAND_JOINT_THUMB_DISTAL_EXT);
    tryGetBonePose(hand, &indexProximalPose, XR_HAND_JOINT_INDEX_PROXIMAL_EXT);
    //__android_log_print(ANDROID_LOG_DEBUG, "PICOEMU", "Getting poses : ");

    glm::vec3 thumbDistalGlobalPosition = glm::vec3(thumbDistalPos.position.x, thumbDistalPos.position.y, thumbDistalPos.position.z);//GLM_POS(thumbDistalPos);
    glm::vec3 indexMetacarpalGlobalPosition = glm::vec3(indexProximalPose.position.x, indexProximalPose.position.y, indexProximalPose.position.z);//GLM_POS(indexProximalPose);

    //glm::quat palmRot = glm::quat(thumbDistalPos.orientation.w, thumbDistalPos.orientation.x, thumbDistalPos.orientation.y, thumbDistalPos.orientation.z);//GLM_QUAT(thumbDistalPos);

    //glm::vec3 indexLocalPos = inverse(palmRot) * (indexGlobalPosition - palmGlobalPosition);

    float distSquare = (thumbDistalPos.position.x - indexProximalPose.position.x) * (thumbDistalPos.position.x - indexProximalPose.position.x)
                       + (thumbDistalPos.position.y - indexProximalPose.position.y) * (thumbDistalPos.position.y - indexProximalPose.position.y)
                       + (thumbDistalPos.position.z - indexProximalPose.position.z) * (thumbDistalPos.position.z - indexProximalPose.position.z);

    bool isActive = distSquare <= 0.002f;//0.03f*0.03f; //TODO CHANGE VALUE 0.001270 min, 0.004 max

    if(hand == XR_HAND_LEFT_EXT){
        bool changedActive = triggerLeftLastState != isActive;
        triggerLeftLastState = isActive;
        data->changedSinceLastSync = changedActive;
    }
    else{
        bool changedActive = triggerRightLastState != isActive;
        triggerRightLastState = isActive;
        data->changedSinceLastSync = changedActive;
    }


    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Hand %d : Distance between index proximal and thumb distal : %.6f, first : %.6f,%.6f,%.6f , second : %.6f,%.6f,%.6f , isActive %d", hand, distSquare,
                        indexProximalPose.position.x, indexProximalPose.position.y, indexProximalPose.position.z, indexProximalPose.position.x, indexProximalPose.position.y, indexProximalPose.position.z, isActive);


    data->currentState = isActive;
}

bool secondaryLeftLastState = false;
bool secondaryRightLastState = false;
void UpdateIfSecondaryButtonPressed(XrHandEXT hand, XrActionStateBoolean *data){
    XrPosef thumbDistalPos;
    XrPosef indexProximalPose;
    tryGetBonePose(hand, &thumbDistalPos, XR_HAND_JOINT_THUMB_DISTAL_EXT);
    tryGetBonePose(hand, &indexProximalPose, XR_HAND_JOINT_INDEX_PROXIMAL_EXT);
    //__android_log_print(ANDROID_LOG_DEBUG, "PICOEMU", "Getting poses : ");

    glm::vec3 thumbDistalGlobalPosition = glm::vec3(thumbDistalPos.position.x, thumbDistalPos.position.y, thumbDistalPos.position.z);//GLM_POS(thumbDistalPos);
    glm::vec3 indexMetacarpalGlobalPosition = glm::vec3(indexProximalPose.position.x, indexProximalPose.position.y, indexProximalPose.position.z);//GLM_POS(indexProximalPose);

    //glm::quat palmRot = glm::quat(thumbDistalPos.orientation.w, thumbDistalPos.orientation.x, thumbDistalPos.orientation.y, thumbDistalPos.orientation.z);//GLM_QUAT(thumbDistalPos);

    //glm::vec3 indexLocalPos = inverse(palmRot) * (indexGlobalPosition - palmGlobalPosition);

    float distSquare = (thumbDistalPos.position.x - indexProximalPose.position.x) * (thumbDistalPos.position.x - indexProximalPose.position.x)
                       + (thumbDistalPos.position.y - indexProximalPose.position.y) * (thumbDistalPos.position.y - indexProximalPose.position.y)
                       + (thumbDistalPos.position.z - indexProximalPose.position.z) * (thumbDistalPos.position.z - indexProximalPose.position.z);

    bool isActive = distSquare >= 0.0035f;//0.03f*0.03f; //TODO CHANGE VALUE 0.001270 min, 0.004 max (0.004 a bit too hard, switched to .0035

    if(hand == XR_HAND_LEFT_EXT){
        bool changedActive = triggerLeftLastState != isActive;
        triggerLeftLastState = isActive;
        data->changedSinceLastSync = changedActive;
    }
    else{
        bool changedActive = triggerRightLastState != isActive;
        triggerRightLastState = isActive;
        data->changedSinceLastSync = changedActive;
    }


    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Hand %d : Distance between index proximal and thumb distal : %.6f, first : %.6f,%.6f,%.6f , second : %.6f,%.6f,%.6f , isActive %d", hand, distSquare,
                        indexProximalPose.position.x, indexProximalPose.position.y, indexProximalPose.position.z, indexProximalPose.position.x, indexProximalPose.position.y, indexProximalPose.position.z, isActive);


    data->currentState = isActive;
}



void UpdateJoystickInput(XrHandEXT hand, XrActionStateVector2f* data){
    XrPosef palmPose;
    XrPosef thumbTipPose;
    tryGetBonePose(hand, &palmPose, XR_HAND_JOINT_PALM_EXT);
    tryGetBonePose(hand, &thumbTipPose, XR_HAND_JOINT_THUMB_DISTAL_EXT);
    //__android_log_print(ANDROID_LOG_DEBUG, "PICOEMU", "Getting poses : ");

    glm::vec3 palmGlobalPosition = glm::vec3(palmPose.position.x, palmPose.position.y, palmPose.position.z);//GLM_POS(palmPose);
    glm::vec3 thumbGlobalPosition = glm::vec3(thumbTipPose.position.x, thumbTipPose.position.y, thumbTipPose.position.z);//GLM_POS(indexTipPose);

    glm::quat palmRot = glm::quat(palmPose.orientation.w, palmPose.orientation.x, palmPose.orientation.y, palmPose.orientation.z);//GLM_QUAT(palmPose);

    glm::vec3 localPalmPosition = glm::inverse(palmRot) * (thumbGlobalPosition - palmGlobalPosition);

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Hand %d : Positions , first : %.6f,%.6f,%.6f", hand,
                        localPalmPosition.x, localPalmPosition.y, localPalmPosition.z);


    //EACH POSITION
    /*
     * MIDDLE : (0.029615,-0.056456,-0.024166)
     * UP : (0.019883,-0.063061,-0.028699)
     * DOWN : (0.047657,-0.043240,-0.013707)
     * LEFT : (-0.043221,-0.055522,-0.028632)
     * RIGHT : (0.008095,-0.071079,-0.026443)
     */
}