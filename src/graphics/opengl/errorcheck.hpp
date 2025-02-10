#pragma once
#include <logging/logging.hpp>
#include <graphics/errors.hpp>

#define GL_CALL(x, ...)                                                 \
    do {                                                                \
        x(__VA_ARGS__);                                                 \
        GLenum error = glGetError();                                    \
        if(error)                                                       \
            MLL_DEBUG(mgl::GLError(error, mll::DebugInfo{#x, __FILE__, (uint)__LINE__})); \
    } while(0)                                          

#define GL_CALLV(x, ...)                                           \
    [&]() {                                                             \
        auto res = x(__VA_ARGS__);                                      \
        GLenum error = glGetError();                                    \
        if(error)                                                       \
            MLL_DEBUG(mgl::GLError(error, mll::DebugInfo{#x, __FILE__, (uint)__LINE__})); \
        return res;                                                     \
    }()