#include <resourceloader/imageloader.hpp>
#include <stb/stb_image.h>
#include <logging/logging.hpp>
#include <resourceloader/errors.hpp>

namespace mrl
{
	// TODO: make my own loader
	ImageData ImageLoader::load(const std::string& filePath)
	{
		stbi_set_flip_vertically_on_load(true);

		int colorChannels, width, height;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &colorChannels, 0);

		if(!data)
			MLL_DEBUG(ResourceError(filePath, stbi_failure_reason()));

		std::string bytes(reinterpret_cast<char*>(data), width * height * colorChannels);
		return ImageData{(uint)colorChannels, (uint)width, (uint)height, bytes};
	}
}
