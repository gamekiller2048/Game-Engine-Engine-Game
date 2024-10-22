#pragma once
#include <array>
#include <graphics/opengl/texture.hpp>

namespace mgl
{
    namespace gl
    {
        class Cubemap : public Texture
        {
        public:
            Cubemap();
            Cubemap(Cubemap&& other) noexcept;

            GLuint getWidth() const;
            GLuint getHeight() const;

            void loadFromFile(const std::array<std::string, 6>& filePaths, GLuint unit, TexFilterOptions filters = {}, bool genMipMap = false);
            void allocate(GLuint width, GLuint height, Format format, Format internalFormat, Primative pixelType, GLuint unit, TexFilterOptions filters = {}, bool genMipMap = false);

        protected:
            GLuint width, height;
        };
    }
}
