#include "handtracking_inputs.h"

#include <android/log.h>

bool initialized = false;
void initializeHands(XrSession session){

    if(initialized) return;
    //Left Hand
    XrHandTrackerCreateInfoEXT createInfoExtLeftHand = {
        .type = XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT,
        .next = NULL,
        .hand = XR_HAND_LEFT_EXT,
        .handJointSet = XR_HAND_JOINT_SET_DEFAULT_EXT
    };
    XrResult leftRes = mirageCreateHandTrackerEXT(session, &createInfoExtLeftHand, &leftHandTracker);

    //Right Hand
    XrHandTrackerCreateInfoEXT createInfoExtRightHand = {
            .type = XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT,
            .next = NULL,
            .hand = XR_HAND_RIGHT_EXT,
            .handJointSet = XR_HAND_JOINT_SET_DEFAULT_EXT
    };
    XrResult rightRes = mirageCreateHandTrackerEXT(session, &createInfoExtRightHand, &rightHandTracker);



    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Initialized Hand tracking! Left Result %d, Right Result %d", leftRes, rightRes);

    initialized = true;
}

void destroyHands(){
    mirageDestroyHandTrackerEXT(leftHandTracker);
    mirageDestroyHandTrackerEXT(rightHandTracker);
}

void updateHandJoints(XrTime currentTime, XrSpace baseSpace, XrHandEXT handType){

    XrHandJointsMotionRangeInfoEXT nextInfo = {
            .type = XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT,
            .next = NULL,
            .handJointsMotionRange =  XR_HAND_JOINTS_MOTION_RANGE_UNOBSTRUCTED_EXT
    };

    XrHandJointsLocateInfoEXT locateInfo = {
            .type = XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT,
            .next = &nextInfo, //XrHandJointsMotionRangeInfoEXT
            .baseSpace = baseSpace,
            .time = currentTime
    };

    XrHandJointLocationsEXT jointLocations = {
            .type = XR_TYPE_HAND_JOINT_LOCATIONS_EXT,
            .next = NULL,
            .isActive = XR_TRUE,
            .jointCount = XR_HAND_JOINT_COUNT_EXT,
            .jointLocations = handType == XR_HAND_LEFT_EXT ? leftJointLocations : rightJointLocations
    };

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Updating hand tracking, time : %d, space : %p", currentTime, baseSpace);

    XrResult result;
    switch(handType){
        case XR_HAND_LEFT_EXT:
            result = mirageLocateHandJointsEXT(leftHandTracker, &locateInfo, &jointLocations);
            //leftJointLocations = jointLocations.jointLocations;
            break;
        case XR_HAND_RIGHT_EXT:
            result = mirageLocateHandJointsEXT(rightHandTracker, &locateInfo, &jointLocations);
            //rightJointLocations = jointLocations.jointLocations;
            break;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "PICOR2", "Updated Hand joints : %d ", result);

}

XrResult tryGetBonePose(XrHandEXT handType, XrPosef* pose, uint32_t bone){ //TODO Transfer FLAGS
    XrHandJointLocationEXT* jointLocationsExt = handType == XR_HAND_LEFT_EXT ? leftJointLocations : rightJointLocations;

    if(jointLocationsExt == NULL) return XR_SUCCESS;

    if(bone >= XR_HAND_JOINT_COUNT_EXT) return XR_ERROR_VALIDATION_FAILURE;

    *pose = jointLocationsExt[bone].pose;

    return XR_SUCCESS;
}