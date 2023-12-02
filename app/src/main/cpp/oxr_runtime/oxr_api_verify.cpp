//TODO COMPLETE FILE

#include "oxr_api_verify.h"
#include "oxr_extension_support.h"
#include "oxr_api_funcs.h"

#include <android/log.h>
#include <stdio.h>

static bool
valid_path_char(const char c) {
    if ('a' <= c && c <= 'z') {
        return true;
    }

    if ('0' <= c && c <= '9') {
        return true;
    }

    if (c == '-' || c == '_' || c == '.' || c == '/') {
        return true;
    }

    return false;
}

XrResult
oxr_verify_extensions(const struct oxr_extension_status *extensions)
{

    if (extensions->EXT_dpad_binding && !extensions->KHR_binding_modification) {
        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "XR_EXT_dpad_binding requires XR_KHR_binding_modification");
        return XR_ERROR_VALIDATION_FAILURE;
    }

    return XR_SUCCESS;
}


enum verify_state
{
    VERIFY_START,
    VERIFY_MIDDLE,
    VERIFY_SLASH,
    VERIFY_SLASHDOTS,
};


XrResult
oxr_verify_full_path_c(const char *path, const char *name)
{
    // XR_MAX_PATH_LENGTH is max including null terminator,
    // length will not include null terminator
    size_t length = XR_MAX_PATH_LENGTH;
    for (size_t i = 0; i < XR_MAX_PATH_LENGTH; i++) {
        if (path[i] == '\0') {
            length = i;
            break;
        }
    }

    return oxr_verify_full_path(path, (uint32_t)length, name);
}

XrResult
oxr_verify_full_path(const char *path, size_t length, const char *name)
{
    enum verify_state state = VERIFY_START;
    bool valid = true;

    if (length >= XR_MAX_PATH_LENGTH) {
        char formatted_path[XR_MAX_PATH_LENGTH + 6];
        snprintf(formatted_path, XR_MAX_PATH_LENGTH + 6, "%s[...]", path);

        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) is too long for a path, must be shorter than %u characters", name, XR_MAX_PATH_LENGTH);
        return XR_ERROR_PATH_FORMAT_INVALID;
    }

    for (uint32_t i = 0; i < length; i++) {
        const char c = path[i];
        switch (state) {
            case VERIFY_START:
                if (c != '/') {
                    __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) does not start with a fowrward slash", name);
                    return XR_ERROR_PATH_FORMAT_INVALID;
                }
                state = VERIFY_SLASH;
                break;
            case VERIFY_SLASH:
                switch (c) {
                    case '.':
                        // Is valid and starts the SlashDot(s) state.
                        state = VERIFY_SLASHDOTS;
                        break;
                    case '/':
                        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) '//' is not a valid in a path", name);
                        return XR_ERROR_PATH_FORMAT_INVALID;
                    default: valid = valid_path_char(c); state = VERIFY_MIDDLE;
                }
                break;
            case VERIFY_MIDDLE:
                switch (c) {
                    case '/': state = VERIFY_SLASH; break;
                    default: valid = valid_path_char(c); state = VERIFY_MIDDLE;
                }
                break;
            case VERIFY_SLASHDOTS:
                switch (c) {
                    case '/':
                        __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) '/.[.]*/' is not a valid in a path", name);
                        return XR_ERROR_PATH_FORMAT_INVALID;
                    case '.':
                        // It's valid, more ShashDot(s).
                        break;
                    default: valid = valid_path_char(c); state = VERIFY_MIDDLE;
                }
                break;
        }

        if (valid) {
            // Can't end with slash
            valid = (path[length - 1] != '/');
        }
        if (!valid) {
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) 0x%02x is not a valid character at position %u",
                                name, c, (uint32_t)length);
            return XR_ERROR_PATH_FORMAT_INVALID;
        }
    }

    switch (state) {
        case VERIFY_START:
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) a empty string is not a valid path", name);
            return XR_ERROR_PATH_FORMAT_INVALID;
        case VERIFY_SLASH:
            // Is this '/path_component/' or '/'
            if (length > 1) {
                // It was '/path_component/'
                return XR_SUCCESS;
            }
            // It was '/'
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) the string '%s' is not a valid path", name, path);
            return XR_ERROR_PATH_FORMAT_INVALID;
        case VERIFY_SLASHDOTS:
            // Does the path ends with '/..'
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : (%s) strings ending with '/.[.]*' is not a valid", name);
            return XR_ERROR_PATH_FORMAT_INVALID;

        case VERIFY_MIDDLE:
            // '/path_component/trailing_path_component' okay!
            return XR_SUCCESS;
        default:
            // We should not end up here.
            __android_log_print(ANDROID_LOG_ERROR, "PICOREUR", "xrStringToPath : ((%s) internal runtime error validating path (%s)",
                                name, path);
            return XR_ERROR_RUNTIME_FAILURE;
    }
}

