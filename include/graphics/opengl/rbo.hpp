#pragma once
#include <glad/gl.h>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/texture.hpp>

namespace mgl
{
    class RBO : public GLObject
    {
    public:
        RBO();
        RBO(RBO&& other) noexcept;
        ~RBO();
        
        void create();

        void bind() const;
        void unbind() const;

        void allocate(GLuint width, GLuint height, Format format) const;
    };
}
