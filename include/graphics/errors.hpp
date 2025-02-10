#pragma once
#include <logging/logging.hpp>

namespace mgl
{
    class GLError : public mll::Error
    {
    public:
        GLError(uint error, const mll::DebugInfo& debugInfo={});
        GLError(const std::string& msg, const mll::DebugInfo& debugInfo={});
    };

    class GLSLError : public GLError
    {
    public:
        GLSLError(const std::string& stage, const std::string& msg);
    };
}
