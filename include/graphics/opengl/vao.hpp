#pragma once
#include <glad/gl.h>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/vbo.hpp>

namespace mgl
{
    namespace gl
    {
        class VAO : public GLObject
        {
        public:
            VAO() = default;
            VAO(VAO&& other) noexcept;
            ~VAO();

            void create();
            void linkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, Primative type, GLsizeiptr stride, GLuint offset) const;
            void bind() const;
            void unbind() const;
        };
    }
}
