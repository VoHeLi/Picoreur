#include "oxr_api_funcs.h"
#include <openxr/openxr_runtime.h>

#include <android/log.h>

#include "graphics_overlay/graphics_test.h"
#include "mirage_app/mirage_main.h"

#define PASS_MIRAGE(function, ...) __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", #function); \
return mirage##function(__VA_ARGS__);

//! OpenXR API function @ep{xrEnumerateSwapchainFormats} //PASS TODO CHECK IF THIS CAUSES PROBLEMS
XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateSwapchainFormats(XrSession session,
                            uint32_t formatCapacityInput,
                            uint32_t *formatCountOutput,
                            int64_t *formats){
    PASS_MIRAGE(EnumerateSwapchainFormats, session, formatCapacityInput, formatCountOutput, formats);
}

//! OpenXR API function @ep{xrCreateSwapchain}
XRAPI_ATTR XrResult XRAPI_CALL
xrCreateSwapchain(XrSession session, const XrSwapchainCreateInfo *createInfo, XrSwapchain *swapchain){



    __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "xr%s called! %u", "Create swapchain facecount", createInfo->faceCount);

    PASS_MIRAGE(CreateSwapchain, session, createInfo, swapchain);
}

//! OpenXR API function @ep{xrDestroySwapchain}
XRAPI_ATTR XrResult XRAPI_CALL
xrDestroySwapchain(XrSwapchain swapchain){
    PASS_MIRAGE(DestroySwapchain, swapchain);
}

//! OpenXR API function @ep{xrEnumerateSwapchainImages}
XRAPI_ATTR XrResult XRAPI_CALL
xrEnumerateSwapchainImages(XrSwapchain swapchain,
                           uint32_t imageCapacityInput,
                           uint32_t *imageCountOutput,
                           XrSwapchainImageBaseHeader *images){

    if(imageCapacityInput == 0){
        PASS_MIRAGE(EnumerateSwapchainImages, swapchain, imageCapacityInput, imageCountOutput, images);
    }

    __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "xr%s called! %l", "EnumerateSwapchainImages Register Swapchain Image", *imageCountOutput);
    XrResult result = mirageEnumerateSwapchainImages(swapchain, imageCapacityInput, imageCountOutput, images);

    registerSwapchainImage(swapchain, images, *imageCountOutput);

    return result;
}

//! OpenXR API function @ep{xrAcquireSwapchainImage}
XRAPI_ATTR XrResult XRAPI_CALL
xrAcquireSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageAcquireInfo *acquireInfo, uint32_t *index){


    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", "AcquireSwapchainImage");
    XrResult res = mirageAcquireSwapchainImage(swapchain, acquireInfo, index);
    if(res < 0) return res;

    updateImage(*index);

    return res;
}

//! OpenXR API function @ep{xrWaitSwapchainImage}
XRAPI_ATTR XrResult XRAPI_CALL
xrWaitSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageWaitInfo *waitInfo){



    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", "WaitSwapchainImage");
    XrResult res = mirageWaitSwapchainImage(swapchain, waitInfo);

    drawTest(swapchain);


    return res;
    //DRAW UNDERLAY
}

//! OpenXR API function @ep{xrReleaseSwapchainImage}
XRAPI_ATTR XrResult XRAPI_CALL
xrReleaseSwapchainImage(XrSwapchain swapchain, const XrSwapchainImageReleaseInfo *releaseInfo){
    //DRAW OVERLAY
    drawTest(swapchain);

    __android_log_print(ANDROID_LOG_DEBUG, "PICOREUR", "xr%s called!", "ReleaseSwapchainImage");
    XrResult res = mirageReleaseSwapchainImage(swapchain, releaseInfo);

    drawTest(swapchain);


    return res;
}