#pragma once

#include <vector>

#include <openxr/openxr_platform.h>

class oxr_instance{
public:
    int _instance_id;
    inline oxr_instance(int instance_id){
        _instance_id = instance_id;
    }

};

struct oxr_path
{
    XrInstance pathInstance;
    const char* pathStr;



};

static std::vector<oxr_path*> currentPaths;


XrResult oxr_path_get_or_create(XrInstance instance, const char* pathString, size_t charLength, oxr_path* path);
XrResult oxr_path_get_string(XrInstance instance, oxr_path* path, const char** str, size_t* length);
