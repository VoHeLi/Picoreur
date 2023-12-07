// Copyright (c) 2017-2023, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0


#include "platformplugin.h"
#include <openxr/openxr_platform.h>

#include <vector>
#include <string>

namespace {
struct AndroidPlatformPlugin : public IPlatformPlugin {
    AndroidPlatformPlugin(void* appVm, void* appActivity) {
        instanceCreateInfoAndroid = {XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR};
        instanceCreateInfoAndroid.applicationVM = appVm;
        instanceCreateInfoAndroid.applicationActivity = appActivity;
    }

    std::vector<std::string> GetInstanceExtensions() const override { return {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME, XR_EXT_HAND_TRACKING_EXTENSION_NAME, XR_EXT_HAND_JOINTS_MOTION_RANGE_EXTENSION_NAME, XR_ULTRALEAP_HAND_TRACKING_FOREARM_EXTENSION_NAME}; }

    XrBaseInStructure* GetInstanceCreateExtension() const override { return (XrBaseInStructure*)&instanceCreateInfoAndroid; }

    void UpdateOptions(const std::shared_ptr<struct Options>& /*unused*/) override {}

    XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid;
};
}  // namespace

std::shared_ptr<IPlatformPlugin> CreatePlatformPlugin(void* vm, void* act) {
    return std::make_shared<AndroidPlatformPlugin>(vm, act);
}

