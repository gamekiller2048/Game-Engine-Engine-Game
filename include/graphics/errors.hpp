#pragma once
#include <logging/logging.hpp>
#include <unordered_map>

namespace mgl
{
    class Win32Error : public mll::Error
    {
    public:
        Win32Error(uint error);
    };
}
