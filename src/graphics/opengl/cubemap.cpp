#include <graphics/opengl/cubemap.hpp>
#include <resourceloader/imageloader.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    Cubemap::Cubemap() :
        Texture(GL_TEXTURE_CUBE_MAP) {}

    Cubemap::Cubemap(Cubemap&& other) noexcept :
        Texture(std::move(other))
    {
        width = other.width;
        height = other.height;
    }

    GLuint Cubemap::getWidth() const
    {
        return width;
    }

    GLuint Cubemap::getHeight() const
    {
        return height;
    }

    void Cubemap::loadFromFile(const std::array<std::string, 6>& filePaths, GLuint unit, TexFilterOptions filters, bool genMipMap)
    {
        this->unit = unit;
        this->width = width;
        this->height = height;
        this->format = format;
        this->internalFormat = format;
        this->pixelType = Primative::UBYTE;
        this->filters = filters;

        setActiveUnit();
        setTexFilters(filters);

        GLenum format;

        for(int i = 0; i < 6; i++) {
            mrl::ImageData imgData = mrl::ImageLoader::load(filePaths[i].c_str());
            width = imgData.width;
            height = imgData.height;

            if(imgData.colorChannels == 1)
                format = GL_RED;
            else if(imgData.colorChannels == 2)
                format = GL_RG;
            else if(imgData.colorChannels == 3)
                format = GL_RGB;
            else
                format = GL_RGBA;

            GL_CALL(glTexImage2D, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imgData.bytes.data());
        }

        if(genMipMap)
            GL_CALL(glGenerateMipmap, gltype);
    }

    void Cubemap::allocate(GLuint width, GLuint height, Format format, Format internalFormat, Primative pixelType, GLuint unit, TexFilterOptions filters, bool genMipMap)
    {
        this->unit = unit;
        this->width = width;
        this->height = height;
        this->format = format;
        this->internalFormat = internalFormat;
        this->pixelType = pixelType;
        this->filters = filters;

        setActiveUnit();
        setTexFilters(filters);

        for(int i = 0; i < 6; i++)
            GL_CALL(glTexImage2D, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLenum)internalFormat, width, height, 0, (GLenum)format, (GLenum)pixelType, (void*)0);

        if(genMipMap)
            GL_CALL(glGenerateMipmap, gltype);
    }
}
