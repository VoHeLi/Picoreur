#include "graphics_test.h"

#include <android/log.h>

void registerGraphicsBinding(XrGraphicsBindingOpenGLESAndroidKHR* bindings){
    context = bindings->context;
    config = bindings->config;
    display = bindings->config;
}

void updateImage(uint32_t image){
    currentImage = image;
}

void registerSwapchainImage(XrSwapchain swapchain, XrSwapchainImageBaseHeader* swapchainImage, int imagesCount){
    swapchainImages.insert(std::make_pair(swapchain, swapchainImage));


}



void drawTest(XrSwapchain swapchain){

    //eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context);

    /*EGLSurface surf = eglGetCurrentSurface(EGL_DRAW);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "Current Surface : %p, EGL_NO_SURFACE : %p", surf, EGL_NO_SURFACE);


    //Create frame buffer
    /*if(m_swapchainFramebuffer == 0){
        glGenFramebuffers(1, &m_swapchainFramebuffer);
    }*/
    /*m_swapchainFramebuffer = 1; //Take the id of the swapchain fbo

    XrSwapchainImageBaseHeader* swapchainImagePack = swapchainImages[swapchain];

    for(int i = 0 ; i< 100; i++){
        XrSwapchainImageBaseHeader* swapchainImage = swapchainImagePack+ currentImage * i;///TODO : undraft this code  16

        const uint32_t colorTexture = reinterpret_cast<const XrSwapchainImageOpenGLESKHR*>(swapchainImage)->image;

        glBindFramebuffer(GL_FRAMEBUFFER, m_swapchainFramebuffer);

        //glBindTexture(GL_TEXTURE_2D, colorTexture+currentImage);
        // Configurer la texture (par exemple, paramètres de filtrage, etc.)
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
        __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "Before calling1! %u %p %p %u fid : %u, %u", colorTexture, swapchainImagePack, swapchainImage, currentImage, m_swapchainFramebuffer, i);

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "Before calling2!");

        //glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

*/

}


void drawTest2(){

    //eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context);

    /*EGLSurface surf = eglGetCurrentSurface(EGL_DRAW);
    __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "2Current Surface : %p, EGL_NO_SURFACE : %p", surf, EGL_NO_SURFACE);


    //Create frame buffer
    /*if(m_swapchainFramebuffer == 0){
        glGenFramebuffers(1, &m_swapchainFramebuffer);
    }*/
    /*m_swapchainFramebuffer = 1; //Take the id of the swapchain fbo

    for(int i = 0; i<100; i++){
        const uint32_t colorTexture = 29;

        glBindFramebuffer(GL_FRAMEBUFFER, m_swapchainFramebuffer);

        //glBindTexture(GL_TEXTURE_2D, colorTexture+currentImage);
        // Configurer la texture (par exemple, paramètres de filtrage, etc.)
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, i, 0);
        __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "2Before calling1! %u %p %p %u fid : %u", i, currentImage, m_swapchainFramebuffer);

        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        __android_log_print(ANDROID_LOG_DEBUG, "PICOG", "2Before calling2!");

        //glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }*/

}