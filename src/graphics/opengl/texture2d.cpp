#include <graphics/opengl/texture2d.hpp>
#include <graphics/opengl/context.hpp>
#include <resourceloader/imageloader.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        Texture2D::Texture2D() :
            Texture(GL_TEXTURE_2D) {}

        Texture2D::Texture2D(Texture2D&& other) noexcept :
            Texture(std::move(other))
        {
            width = other.width;
            height = other.height;
        }

        GLuint Texture2D::getWidth() const
        {
            return width;
        }

        GLuint Texture2D::getHeight() const
        {
            return height;
        }

        void Texture2D::loadFromFile(const std::string& filePath, GLuint unit, TexFilterOptions filters, bool genMipMap)
        {
            mrl::ImageData imgData = mrl::ImageLoader::load(filePath);
            width = imgData.width;
            height = imgData.height;

            if(imgData.colorChannels == 1)
                format = Format::RED;
            else if(imgData.colorChannels == 2)
                format = Format::RG;
            else if(imgData.colorChannels == 3)
                format = Format::RGB;
            else
                format = Format::RGBA;

            this->unit = unit;
            this->width = width;
            this->height = height;
            this->format = format;
            this->internalFormat = format;
            this->pixelType = Primative::UBYTE;
            this->filters = filters;

            setActiveUnit();
            setTexFilters(filters);

            GL_CALL(glTexImage2D, gltype, 0, (GLenum)internalFormat, width, height, 0, (GLenum)format, (GLenum)pixelType, imgData.bytes.data());

            if(genMipMap)
                GL_CALL(glGenerateMipmap, gltype);
        }

        void Texture2D::allocate(GLuint width, GLuint height, Format format, Format internalFormat, Primative pixelType, GLuint unit, TexFilterOptions filters, bool genMipMap)
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

            GL_CALL(glTexImage2D, gltype, 0, (GLenum)internalFormat, width, height, 0, (GLenum)format, (GLenum)pixelType, (void*)0);

            if(genMipMap)
                GL_CALL(glGenerateMipmap, gltype);
        }

        void Texture2D::write(const void* data, const mml::ivec4& bounds) const
        {
            bind();
            if(bounds == mml::ivec4(-1, -1, -1, -1))
                GL_CALL(glTexSubImage2D, gltype, 0, 0, 0, width, height, (GLenum)format, (GLenum)pixelType, data);
            else
                GL_CALL(glTexSubImage2D, gltype, 0, bounds.x, bounds.y, bounds.z, bounds.w, (GLenum)format, (GLenum)pixelType, data);
        }
    }
}

