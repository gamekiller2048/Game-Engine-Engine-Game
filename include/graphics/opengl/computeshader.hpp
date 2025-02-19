#pragma once
#include <graphics/opengl/shader.hpp>

namespace mgl
{
    namespace gl
    {
        enum class MemoryBarrier : GLuint
        {
            VERTEX_ATTRIB_ARRAY=GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
            ELEMENT_ARRAY=GL_ELEMENT_ARRAY_BARRIER_BIT,
            UNIFORM_BARRIER=GL_UNIFORM_BARRIER_BIT,
            TEXTURE_FETCH=GL_TEXTURE_FETCH_BARRIER_BIT,
            SHADER_IMAGE_ACCESS=GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
            COMMAND=GL_COMMAND_BARRIER_BIT,
            PIXEL_BUFFER=GL_PIXEL_BUFFER_BARRIER_BIT,
            TEXTURE_UPDATE=GL_TEXTURE_UPDATE_BARRIER_BIT,
            BUFFER_UPDATE=GL_BUFFER_UPDATE_BARRIER_BIT,
            FRAMEBUFFER=GL_FRAMEBUFFER_BARRIER_BIT,
            TRANSFORM_FEEDBACK=GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
            ATOMIC_COUNTER=GL_ATOMIC_COUNTER_BARRIER_BIT,
            ALL=GL_ALL_BARRIER_BITS
        };

        class ComputeShader : public Shader
        {
            public:
                ComputeShader();
        };
    }
}
