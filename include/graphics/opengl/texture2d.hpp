#pragma once
#include <memory>
#include <graphics/opengl/texture.hpp>
#include <graphics/opengl/enums.hpp>

namespace mgl
{
    namespace gl
    {
        class Texture2D : public Texture
        {
        public:
            Texture2D();
            Texture2D(Texture2D&& other) noexcept;

            GLuint getWidth() const;
            GLuint getHeight() const;

            void loadFromFile(const std::string& filePath, GLuint unit, TexFilterOptions filters = {}, bool genMipMap = false);
            void allocate(GLuint width, GLuint height, Format format, Format internalFormat, Primative pixelType, GLuint unit, TexFilterOptions filters = {}, bool genMipMap = false);
            void write(const void* data, const mml::ivec4& bounds = mml::ivec4(-1, -1, -1, -1)) const;

        protected:
            GLuint width, height;
        };
    }
}
