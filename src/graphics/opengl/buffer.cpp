#include <graphics/opengl/buffer.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    Buffer::Buffer(BufferType type) :
        GLObject((GLenum)type) {}

    Buffer::Buffer(Buffer&& other) noexcept :
        GLObject(std::move(other)) {}

    Buffer::~Buffer()
    {
        GL_CALL(glDeleteBuffers, 1, &id);
    }

    void Buffer::create()
    {
        GL_CALL(glGenBuffers, 1, &id);
    }

    void Buffer::bind() const
    {
        GL_CALL(glBindBuffer, gltype, id);
    }

    void Buffer::unbind() const
    {
        GL_CALL(glBindBuffer, gltype, 0);
    }

    GLint Buffer::getParameterInt(BufferParam param) const
    {
        GLint result;
        GL_CALL(glGetBufferParameteriv, gltype, (GLenum)param, &result);
        return result;
    }

    GLint64 Buffer::getParameterInt64(BufferParam param) const
    {
        GLint64 result;
        GL_CALL(glGetBufferParameteri64v, gltype, (GLenum)param, &result);
        return result;
    }

    void Buffer::unmap() const
    {
        GL_CALL(glUnmapBuffer, gltype);
    }
}