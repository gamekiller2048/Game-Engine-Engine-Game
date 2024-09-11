#include <resourceloader/errors.hpp>

namespace mrl
{
    ResourceError::ResourceError(const std::string& filePath, const std::string& msg) :
        Error("Resource", "In " + filePath + ", " + msg) {}
}
