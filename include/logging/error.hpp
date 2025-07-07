#pragma once
#include <logging/logable.hpp>

namespace mll
{
    class Error : public Logable
    {
    public:
        Error(const std::string& name, const std::string message="", const DebugInfo& debugInfo={});
    };
}