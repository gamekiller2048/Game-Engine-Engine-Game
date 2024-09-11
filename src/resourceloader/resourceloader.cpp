#include <resourceloader/resourceloader.hpp>
#include <fstream>
#include <logging/logging.hpp>
#include <resourceloader/errors.hpp>

namespace mrl
{
    std::string ResourceLoader::read(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if(!file)
            MLL_DEBUG(ResourceError(filePath, "failed to open"));

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string bytes((uint)size, '\0');

        if(!file.read(&bytes[0], size))
            MLL_DEBUG(ResourceError(filePath, "failed to read"))

        return bytes;
    }

    std::string ResourceLoader::readBytes(const std::string& filePath)
	{
        std::ifstream file(filePath, std::ios::binary);
        if(!file)
            MLL_DEBUG(ResourceError(filePath, "failed to open"));

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string bytes((uint)size, '\0');

        if(!file.read(&bytes[0], size))
            MLL_DEBUG(ResourceError(filePath, "failed to read"))
        
        return bytes;
	}
}
