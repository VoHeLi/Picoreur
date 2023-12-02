// Copyright 2019-2020, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief  Holds path related functions.
 * @author Jakob Bornecrantz <jakob@collabora.com>
 * @ingroup oxr_main
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "oxr_objects.h"



/*!
 * Internal representation of a path, item follows this struct in memory and
 * that in turn is followed by the string.
 *
 * @ingroup oxr_main
 */

XrResult oxr_path_get_or_create(XrInstance instance, const char* pathString, size_t charLength, oxr_path* path){


    for(oxr_path* currentPath : currentPaths){
        if(currentPath->pathInstance == instance && (strcmp(currentPath->pathStr,path->pathStr)==0)){
            *path = *currentPath;
            return XR_SUCCESS;
        }
    }

    path = new oxr_path{instance, pathString};
    currentPaths.push_back(path);
    return XR_SUCCESS;
}

XrResult oxr_path_get_string(XrInstance instance, oxr_path* path, const char** str, size_t* length){
    if(instance == path->pathInstance){
        *str = path->pathStr;
        *length = strlen(path->pathStr);
        return XR_SUCCESS;
    }
    return XR_ERROR_INSTANCE_LOST;
}

/*
 *
 * Helpers
 *
 */

