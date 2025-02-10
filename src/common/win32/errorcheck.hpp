#pragma once
#include <logging/logging.hpp>
#include <common/win32/errors.hpp>

// check error using GetLastError()
#define WIN_CALL(x, ...)                                                \
    do {                                                                \
        x(__VA_ARGS__);                                                 \
        uint error = (uint)GetLastError();                              \
        if(error)                                                       \
            MLL_LOG(mcl::Win32Error(error, mll::DebugInfo{#x, __FILE__, (uint)__LINE__})); \
    } while(0)                                          

// return value and check error if the value is NULL
#define WIN_CALLV(x, ...)                                               \
    [&]() {                                                             \
        auto res = x(__VA_ARGS__);                                      \
        if(res == NULL)                                                 \
            MLL_LOG(mcl::Win32Error((uint)GetLastError(), mll::DebugInfo{#x, __FILE__, (uint)__LINE__})); \
        return res;                                                     \
    }()

// return value and check error using GetLastError()
#define WIN_CALLR(x, ...)                                               \
    [&]() {                                                             \
        auto res = x(__VA_ARGS__);                                      \
        uint error = (uint)GetLastError();                              \
        if(error)                                                       \
            MLL_LOG(mcl::Win32Error(error, mll::DebugInfo{#x, __FILE__, (uint)__LINE__})); \
        return res;                                                     \
    }()