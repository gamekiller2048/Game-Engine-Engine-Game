#include <logging/info.hpp>

namespace mll
{
    Info::Info(const std::string& name, const std::string message, const DebugInfo& debugInfo) :
        Logable(Severity::INFO, name, message, debugInfo) {}
}