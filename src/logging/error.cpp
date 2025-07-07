#include <logging/error.hpp>

namespace mll
{
    Error::Error(const std::string& name, const std::string message, const DebugInfo& debugInfo) :
        Logable(Severity::MAJOR, name, message, debugInfo) {}
}