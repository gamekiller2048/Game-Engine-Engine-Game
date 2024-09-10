#pragma once
#include <logging/logging.hpp>
#include <graphics/errors.hpp>

// check error using GetLastError()
#define WIN_CALL(x, ...)                                                \
    do {                                                                \
        x(__VA_ARGS__);                                                 \
        uint error = (uint)GetLastError();                              \
        if(error)                                                       \
            MLL_LOG(mgl::Win32Error(error));                            \
    } while(0)                                          

// return value and check error if the value is NULL
#define WIN_CALLV(x, ...)                                               \
    [&]() {                                                             \
        auto res = x(__VA_ARGS__);                                      \
        if(res == NULL)                                                 \
            MLL_LOG(mgl::Win32Error((uint)GetLastError()));             \
        return res;                                                     \
    }()

// return value and check error using GetLastError()
#define WIN_CALLR(x, ...)                                               \
    [&]() {                                                             \
        auto res = x(__VA_ARGS__);                                      \
        uint error = (uint)GetLastError();                              \
        if(error)                                                       \
            MLL_LOG(mgl::Win32Error(error));                       \
        return res;                                                     \
    }()