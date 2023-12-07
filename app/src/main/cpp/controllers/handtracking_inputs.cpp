#include "handtracking_inputs.h"

#include <android/log.h>

bool initialized = false;
void initializeHands(XrSession session){

    if(initialized) return;
    //Left Hand
    XrHandTrackerCreateInfoEXT createInfoExtLeftHand = {
        type : XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT,
        next : NULL,
        hand : XR_HAND_LEFT_EXT,
        handJointSet : XR_HAND_JOINT_SET_DEFAULT_EXT
    };
    XrResult leftRes = mirageCreateHandTrackerEXT(session, &createInfoExtLeftHand, &leftHandTracker);

    //Right Hand
    XrHandTrackerCreateInfoEXT createInfoExtRightHand = {
            type : XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT,
            next : NULL,
            hand : XR_HAND_RIGHT_EXT,
            handJointSet : XR_HAND_JOINT_SET_DEFAULT_EXT
    };
    XrResult rightRes = mirageCreateHandTrackerEXT(session, &createInfoExtRightHand, &rightHandTracker);

    leftJointLocations = XrHandJointLocationsEXT();
    rightJointLocations = XrHandJointLocationsEXT();

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Initialized Hand tracking! Left Result %d, Right Result %d", leftRes, rightRes);

    initialized = true;
}

void destroyHands(){
    mirageDestroyHandTrackerEXT(leftHandTracker);
    mirageDestroyHandTrackerEXT(rightHandTracker);
}

void updateHandJoints(XrTime currentTime, XrSpace currentSpace, XrHandEXT handType){
    XrHandJointsLocateInfoEXT locateInfo = {
            type : XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT,
            next : NULL,
            baseSpace : currentSpace,
            time :  currentTime
    };

    XrResult result;
    switch(handType){
        case XR_HAND_LEFT_EXT:
            result = mirageLocateHandJointsEXT(leftHandTracker, &locateInfo, &leftJointLocations);
            break;
        case XR_HAND_RIGHT_EXT:
            result = mirageLocateHandJointsEXT(rightHandTracker, &locateInfo, &rightJointLocations);
            break;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Updated Hand joints : %d ", result);

}

XrResult tryGetPalmPosition(XrHandEXT handType, XrPosef* pose){ //TODO Transfer FLAGS
    XrHandJointLocationsEXT jointLocationsExt = handType == XR_HAND_LEFT_EXT ? leftJointLocations : rightJointLocations;

    if(!jointLocationsExt.isActive){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Hand %d non-active", handType);
        return XR_SUCCESS;
    }

    int jointsCount = jointLocationsExt.jointCount;

    if(jointsCount <= XR_HAND_JOINT_PALM_EXT){
        __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Not enought bones", handType);
    }

    XrHandJointLocationEXT handJointLoc = jointLocationsExt.jointLocations[XR_HAND_JOINT_PALM_EXT];
    *pose = handJointLoc.pose;
}