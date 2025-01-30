#pragma once
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/vao.hpp>

namespace mgl
{
    class GLVertexBufferImpl
    {
    public:
        gl::VBO vbo;
        gl::VAO vao; // required to use vbo in core profile
    };
}