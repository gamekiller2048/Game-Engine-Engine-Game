#pragma once
#include <resourceloader/resourceloader.hpp>

namespace mrl
{
    struct ImageData
    {
        uint colorChannels, width, height;
        std::string bytes;
    };

    class ImageLoader : ResourceLoader
    {
    public:
        static ImageData load(const std::string& filePath);
    };
}