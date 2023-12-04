#include "oxr_api_funcs.h"

#include <android/log.h>

#include "mirage_app/mirage_main.h"
#include "controllers/controllers_binding.h"

#define PASS_MIRAGE(function, ...) __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", #function); \
XrResult res = mirage##function(__VA_ARGS__); \
__android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called with result : %p", #function, res);\
return res;

XRAPI_ATTR XrResult XRAPI_CALL
xrSetDebugUtilsObjectNameEXT(XrInstance instance, const XrDebugUtilsObjectNameInfoEXT *nameInfo);


XRAPI_ATTR XrResult XRAPI_CALL
xrCreateDebugUtilsMessengerEXT(XrInstance instance,
                               const XrDebugUtilsMessengerCreateInfoEXT *createInfo,
                               XrDebugUtilsMessengerEXT *messenger);


XRAPI_ATTR XrResult XRAPI_CALL
xrDestroyDebugUtilsMessengerEXT(XrDebugUtilsMessengerEXT messenger);


XRAPI_ATTR XrResult XRAPI_CALL
xrSubmitDebugUtilsMessageEXT(XrInstance instance,
                             XrDebugUtilsMessageSeverityFlagsEXT messageSeverity,
                             XrDebugUtilsMessageTypeFlagsEXT messageTypes,
                             const XrDebugUtilsMessengerCallbackDataEXT *callbackData);


XRAPI_ATTR XrResult XRAPI_CALL
xrSessionBeginDebugUtilsLabelRegionEXT(XrSession session, const XrDebugUtilsLabelEXT *labelInfo);


XRAPI_ATTR XrResult XRAPI_CALL
xrSessionEndDebugUtilsLabelRegionEXT(XrSession session);

/
XRAPI_ATTR XrResult XRAPI_CALL
xrSessionInsertDebugUtilsLabelEXT(XrSession session, const XrDebugUtilsLabelEXT *labelInfo);