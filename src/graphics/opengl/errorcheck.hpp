#pragma once
#include <logging/logging.hpp>
#include <graphics/errors.hpp>

#define GL_CALL(x, ...)                                                 \
    do {                                                                \
        x(__VA_ARGS__);                                                 \
        GLenum error = glGetError();                                    \
        if(error)                                                       \
            MLL_DEBUG(mgl::GLError(error));                             \
    } while(0)                                          

#define GL_CALLV(x, ...)                                           \
    [&]() {                                                             \
        auto res = x(__VA_ARGS__);                                      \
        GLenum error = glGetError();                                    \
        if(error)                                                       \
            MLL_DEBUG(mgl::GLError(error));                             \
        return res;                                                     \
    }()