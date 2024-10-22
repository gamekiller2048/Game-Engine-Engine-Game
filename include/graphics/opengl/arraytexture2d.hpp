#pragma once
#include <graphics/opengl/texture.hpp>
#include <vector>

namespace mgl
{
    namespace gl
    {
        class ArrayTexture2D : public Texture
        {
        public:
            ArrayTexture2D();
            ArrayTexture2D(ArrayTexture2D&& other) noexcept;

            GLuint getWidth() const;
            GLuint getHeight() const;
            GLuint getNumTextures() const;

            void loadFromFile(const std::vector<std::string>& filePaths, GLuint unit, TexFilterOptions filters = {}, bool genMipMap = false);
            void allocate(GLuint width, GLuint height, GLuint depth, Format format, Format internalFormat, Primative pixelType, GLuint unit, TexFilterOptions filters = {}, bool genMipMap = false);
            void write(GLuint texNum, const void* data);

        protected:
            GLuint width, height, depth;
        };
    }
}
