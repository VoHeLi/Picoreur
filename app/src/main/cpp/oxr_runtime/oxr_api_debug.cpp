#include "oxr_api_funcs.h"

#include <android/log.h>

#include "mirage_app/mirage_main.h"
#include "controllers/controllers_binding.h"

#define PASS_MIRAGE(function, ...) __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", #function); \
XrResult res = mirage##function(__VA_ARGS__); \
__android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called with result : %p", #function, res);\
return res;

XRAPI_ATTR XrResult XRAPI_CALL
xrSetDebugUtilsObjectNameEXT(XrInstance instance, const XrDebugUtilsObjectNameInfoEXT *nameInfo){
    PASS_MIRAGE(SetDebugUtilsObjectNameEXT, nameInfo);
}


XRAPI_ATTR XrResult XRAPI_CALL
xrCreateDebugUtilsMessengerEXT(XrInstance instance,
                               const XrDebugUtilsMessengerCreateInfoEXT *createInfo,
                               XrDebugUtilsMessengerEXT *messenger){
    PASS_MIRAGE(CreateDebugUtilsMessengerEXT, createInfo, messenger);
}


XRAPI_ATTR XrResult XRAPI_CALL
xrDestroyDebugUtilsMessengerEXT(XrDebugUtilsMessengerEXT messenger){
    PASS_MIRAGE(DestroyDebugUtilsMessengerEXT, messenger);
}


XRAPI_ATTR XrResult XRAPI_CALL
xrSubmitDebugUtilsMessageEXT(XrInstance instance,
                             XrDebugUtilsMessageSeverityFlagsEXT messageSeverity,
                             XrDebugUtilsMessageTypeFlagsEXT messageTypes,
                             const XrDebugUtilsMessengerCallbackDataEXT *callbackData){
    PASS_MIRAGE(SubmitDebugUtilsMessageEXT, messageSeverity, messageTypes, callbackData);
}


XRAPI_ATTR XrResult XRAPI_CALL
xrSessionBeginDebugUtilsLabelRegionEXT(XrSession session, const XrDebugUtilsLabelEXT *labelInfo){
    PASS_MIRAGE(SessionBeginDebugUtilsLabelRegionEXT, labelInfo);
}


XRAPI_ATTR XrResult XRAPI_CALL
xrSessionEndDebugUtilsLabelRegionEXT(XrSession session){
    PASS_MIRAGE(SessionEndDebugUtilsLabelRegionEXT, session);
}


XRAPI_ATTR XrResult XRAPI_CALL
xrSessionInsertDebugUtilsLabelEXT(XrSession session, const XrDebugUtilsLabelEXT *labelInfo){
    PASS_MIRAGE(SessionInsertDebugUtilsLabelEXT, session, labelInfo);
}