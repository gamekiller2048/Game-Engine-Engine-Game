#include <graphics/opengl/arraytexture2d.hpp>
#include "errorcheck.hpp"
#include <resourceloader/imageloader.hpp>

namespace mgl
{
    namespace gl
    {
        ArrayTexture2D::ArrayTexture2D() :
            Texture(GL_TEXTURE_2D_ARRAY) {}

        ArrayTexture2D::ArrayTexture2D(ArrayTexture2D&& other) noexcept :
            Texture(std::move(other))
        {
            width = other.width;
            height = other.height;
            depth = other.depth;
        }

        GLuint ArrayTexture2D::getWidth() const
        {
            return width;
        }

        GLuint ArrayTexture2D::getHeight() const
        {
            return height;
        }

        GLuint ArrayTexture2D::getNumTextures() const
        {
            return width;
        }

        void ArrayTexture2D::loadFromFile(const std::vector<std::string>& filePaths, GLuint unit, TexFilterOptions filters, bool genMipMap)
        {
            bool _init = false;
            uint depth = 0;

            for(const std::string& filePath : filePaths) {
                mrl::ImageData imgData = mrl::ImageLoader::load(filePath);
            
                if(!_init) {
                    if(imgData.colorChannels == 1)
                        format = Format::RED;
                    else if(imgData.colorChannels == 2)
                        format = Format::RG;
                    else if(imgData.colorChannels == 3)
                        format = Format::RGB;
                    else
                        format = Format::RGBA;

                    this->unit = unit;
                    this->width = imgData.width;
                    this->height = imgData.height;
                    this->depth = filePaths.size();
                    this->format = format;
                    this->internalFormat = format;
                    this->pixelType = Primative::UBYTE;
                    this->filters = filters;

                    setActiveUnit();
                    setTexFilters(filters);

                    GL_CALL(glTexImage3D, gltype, 0, (GLenum)internalFormat, width, height, filePaths.size(), 0, (GLenum)format, (GLenum)pixelType, nullptr);

                    if(genMipMap)
                        GL_CALL(glGenerateMipmap, gltype);

                    _init = true;
                }

                GL_CALL(glTexSubImage3D, gltype, 0, 0, 0, depth, width, height, 1, (GLenum)format, GLenum(pixelType), imgData.bytes.data());
                depth++;
            }
        }

        void ArrayTexture2D::allocate(GLuint width, GLuint height, GLuint depth, Format format, Format internalFormat, Primative pixelType, GLuint unit, TexFilterOptions filters, bool genMipMap)
        {
            this->unit = unit;
            this->width = width;
            this->height = height;
            this->depth = depth;
            this->format = format;
            this->internalFormat = internalFormat;
            this->pixelType = pixelType;

            setActiveUnit();
            setTexFilters(filters);

            GL_CALL(glTexImage3D, gltype, 0, (GLenum)internalFormat, width, height, depth, 0, (GLenum)format, (GLenum)pixelType, NULL);

            if(genMipMap)
                GL_CALL(glGenerateMipmap, gltype);
        }

        void ArrayTexture2D::write(GLuint texNum, const void* data)
        {
            bind();
            GL_CALL(glTexSubImage3D, gltype, 0, 0, 0, texNum, width, height, 1, (GLenum)format, (GLenum)pixelType, data);
        }
    }
}
