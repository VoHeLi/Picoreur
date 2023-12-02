#pragma once

#ifndef MIRAGE_LOADER
#define MIRAGE_LOADER

#include <jni.h>
#include "openxr/openxr_runtime.h"


#include "platformplugin.h"

static void* lynxLoaderHandle;

static JNIEnv* runtimeJniEnv;
static jobject runtimeJavaObject;

XrResult loadLynxOpenXR();

XrResult loadRuntimeContext(JNIEnv *env, jobject thiz);

XrResult m_xrGetInstanceProcAddr(XrInstance instance, const char* name, PFN_xrVoidFunction* function);
#endif