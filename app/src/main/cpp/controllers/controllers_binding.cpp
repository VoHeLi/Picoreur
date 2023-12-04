
#include "controllers_binding.h"

#include <string>
#include <cmath>
#include <ctime>
#include <chrono>

#include <android/log.h>

void TryRegisterControllerPath(XrPath path, const char* pathStr){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "TryRegisterControllerPath : %p, %s ", path, pathStr);
    if(strcmp(pathStr, handSpacesPathNames[LEFT_HAND])){
        handPaths[LEFT_HAND] = path;
    }
    else if(strcmp(pathStr, handSpacesPathNames[RIGHT_HAND])){
        handPaths[RIGHT_HAND] = path;
    }
    else if(strcmp(pathStr, "/interaction_profiles/bytedance/pico4_controller")){
        interactionProfilePath = path;
    }
    else{
        for(int i = 0; i < 33; i++){
            if(strcmp(pathStr, controllerPathNames[i])){
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

void GetControllerSpacePose(XrSpace space, XrPosef* pose){
    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "GetControllerSpacePose : %p", space);
    //if(space == handSpaces[LEFT_HAND]){
        auto now = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        // Convertir les millisecondes en secondes
        float seconds = milliseconds / 1000.0;

        // Fréquence de la sinusoïde (par exemple, 1 cycle par seconde)
        float frequency = 0.5;

        // Amplitude de la sinusoïde (ajustez selon vos besoins)
        float amplitude = 2.0;

        // Calculer la valeur sinusoidale
        float sinusoidalValue = amplitude * sin(2 * M_PI * frequency * seconds);

        pose->position.x = sinusoidalValue;
    //}
    /*else if(space == handSpaces[RIGHT_HAND]){
        auto now = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        // Convertir les millisecondes en secondes
        float seconds = milliseconds / 1000.0;

        // Fréquence de la sinusoïde (par exemple, 1 cycle par seconde)
        float frequency = 2;

        // Amplitude de la sinusoïde (ajustez selon vos besoins)
        float amplitude = 0.3;

        // Calculer la valeur sinusoidale
        float sinusoidalValue = amplitude * sin(2 * M_PI * frequency * seconds);

        pose->position.y = sinusoidalValue;
    }*/

}

void TryRegisterActionSet(XrActionSet actionSet, const char* actionSetName){
    if(strcmp(actionSetName, controllersActionSetName)){
        controllersActionSet = actionSet;
    }
}

void TryRegisterAction(XrAction action, const char* actionName){
    for(int i = 0; i < 17; i++){
        if(strcmp(actionName, controllersActionsNames[i])){
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