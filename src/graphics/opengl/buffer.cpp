#include <graphics/opengl/buffer.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
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

        void Buffer::allocate(const void* buffer, GLsizei size, UsagePattern usage) const
        {
            GL_CALL(glBufferData, gltype, size, buffer, (GLenum)usage);
        }

        template<typename T>
        void Buffer::allocate(const std::vector<T>& buffer, UsagePattern usage) const
        {
            GL_CALL(glBufferData, gltype, buffer.size() * sizeof(T), buffer.data(), (GLenum)usage);
        }

        template<typename T>
        void Buffer::allocate(GLsizei size, UsagePattern usage) const
        {
            GL_CALL(glBufferData, gltype, size, nullptr, (GLenum)usage);
        }

        void Buffer::write(const void* buffer, GLsizei size, GLintptr start, GLsizei end) const
        {
            GL_CALL(glBufferSubData, gltype, start, end == -1 ? end : size, buffer);
        }

        template<typename T>
        void Buffer::write(const std::vector<T>& buffer, GLintptr start, GLsizei end) const
        {
            GL_CALL(glBufferSubData, gltype, start, end == -1 ? end : buffer.size() * sizeof(T), buffer.data());
        }

        template<typename T>
        void* Buffer::map(std::vector<T>& buffer, Access access) const
        {
            return GL_CALLV(glMapBuffer, gltype, (GLenum)access);
        }

        template<typename T>
        void Buffer::read(std::vector<T>& buffer, GLintptr start, GLsizei end) const
        {
            GL_CALL(glGetBufferSubData, gltype, start, end == -1 ? end : buffer.size() * sizeof(T), buffer.data());
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
}