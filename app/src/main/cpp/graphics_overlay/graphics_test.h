#pragma once

#include <openxr/openxr_platform.h>
#include <GLES2/gl2.h>
#include <map>
#include <vector>

static EGLDisplay display;
static EGLConfig config;
static EGLContext context;

static uint32_t currentImage;

static GLuint m_swapchainFramebuffer;

static std::map<XrSwapchain, XrSwapchainImageBaseHeader*> swapchainImages;

void registerGraphicsBinding(XrGraphicsBindingOpenGLESAndroidKHR* bindings);
void registerSwapchainImage(XrSwapchain swapchain, XrSwapchainImageBaseHeader* swapchainImage, int imagesCount);

void drawTest(XrSwapchain swapchain);
void drawTest2();

void updateImage(uint32_t image);

