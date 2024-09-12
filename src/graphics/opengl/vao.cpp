#include <graphics/opengl/vao.hpp>
#include <glad/gl.h>
#include "errorcheck.hpp"

namespace mgl
{
    VAO::~VAO()
    {
        GL_CALL(glDeleteVertexArrays, 1, &id);
    }

    VAO::VAO(VAO&& other) noexcept :
        GLObject(std::move(other)) {}

    void VAO::create()
    {
        GL_CALL(glGenVertexArrays, 1, &id);
        bind();
    }

    void VAO::linkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, Primative type, GLsizeiptr stride, GLuint offset) const
    {
        vbo.bind();

        if(type == Primative::FLOAT)
            GL_CALL(glVertexAttribPointer, layout, numComponents, (GLenum)type, GL_FALSE, stride, reinterpret_cast<void*>(offset));
        else if(type == Primative::UINT)
            GL_CALL(glVertexAttribIPointer, layout, numComponents, (GLenum)type, stride, reinterpret_cast<void*>(offset));
        else if(type == Primative::DOUBLE)
            GL_CALL(glVertexAttribLPointer, layout, numComponents, (GLenum)type, stride, reinterpret_cast<void*>(offset));

        GL_CALL(glEnableVertexAttribArray, layout);
        vbo.unbind();
    }

    void VAO::bind() const
    {
        GL_CALL(glBindVertexArray, id);
    }

    void VAO::unbind() const
    {
        GL_CALL(glBindVertexArray, 0);
    }
}
