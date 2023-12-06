
#include "controllers_binding.h"

#include <string>
#include <cmath>
#include <ctime>
#include <chrono>

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

void TryRegisterControllerSpace(XrSpace space, XrPath path){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryRegisterControllerSpace : %p, %p ", space, path);
    if(path == handPaths[LEFT_HAND]){
        handSpaces[LEFT_HAND] = space;
    }
    else if(path == handPaths[RIGHT_HAND]){
        handSpaces[RIGHT_HAND] = space;
    }
}

void GetControllerSpacePose(XrSpace space, XrSpaceLocation *location){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "GetControllerSpacePose : %p", space);
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    location->locationFlags = XR_SPACE_LOCATION_POSITION_TRACKED_BIT | XR_SPACE_LOCATION_POSITION_VALID_BIT | XR_SPACE_LOCATION_ORIENTATION_VALID_BIT | XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT;
    location->pose.position.x = r;
}

void TryRegisterActionSet(XrActionSet actionSet, const char* actionSetName){
    if(strcmp(actionSetName, controllersActionSetName) == 0){
        controllersActionSet = actionSet;
    }
}

void TryRegisterAction(XrAction action, const char* actionName){
    for(int i = 0; i < 17; i++){
        if(strcmp(actionName, controllersActionsNames[i]) == 0){
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
