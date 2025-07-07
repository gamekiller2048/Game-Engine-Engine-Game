#pragma once

namespace mrl
{
    class ResourceLoader
    {
    public:
        static std::string read(const std::string& filePath);
        static std::string readBytes(const std::string& filePath);
    };
}