#pragma once
#include <logging/logging.hpp>

namespace mgl
{
    class GLError : public mll::Error
    {
    public:
        GLError(uint error);
        GLError(const std::string& msg);
    };

    class GLSLError : public GLError
    {
    public:
        GLSLError(const std::string& stage, const std::string& msg);
    };
}
