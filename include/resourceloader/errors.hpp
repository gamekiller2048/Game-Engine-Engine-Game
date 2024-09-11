#pragma once
#include <logging/error.hpp>

namespace mrl
{
    class ResourceError : public mll::Error
    {
    public:
        ResourceError(const std::string& filePath, const std::string& msg);
    };
}
