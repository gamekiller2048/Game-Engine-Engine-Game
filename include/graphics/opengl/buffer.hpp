#pragma once
#include <vector>
#include <glad/gl.h>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/enums.hpp>

namespace mgl
{
    namespace gl
    {
        enum class BufferType : GLuint
        {
            VERTEX = GL_ARRAY_BUFFER,
            ELEMENT = GL_ELEMENT_ARRAY_BUFFER
        };

        enum class BufferParam : GLuint
        {
            ACCESS = GL_BUFFER_ACCESS,
            ACCESS_FLAGS = GL_BUFFER_ACCESS_FLAGS,
            MAP_LENGTH = GL_BUFFER_MAP_LENGTH,
            MAP_OFFSET = GL_BUFFER_MAP_OFFSET,
            SIZE = GL_BUFFER_SIZE,
            USAGE = GL_BUFFER_USAGE
        };

        class Buffer : public GLObject
        {
        public:
            Buffer(BufferType type);
            Buffer(Buffer&& other) noexcept;
            ~Buffer();

            void create();
            void bind() const;
            void unbind() const;

            GLint getParameterInt(BufferParam param) const;
            GLint64 getParameterInt64(BufferParam param) const;

            void allocate(const void* buffer, GLsizei size, UsagePattern usage) const;

            template<typename T>
            void allocate(const std::vector<T>& buffer, UsagePattern usage) const;

            template<typename T>
            void allocate(GLsizei size, UsagePattern usage) const;

            void write(const void* buffer, GLsizei size, GLintptr start = 0, GLsizei end = -1) const;

            template<typename T>
            void write(const std::vector<T>& buffer, GLintptr start = 0, GLsizei end = -1) const;

            template<typename T>
            void* map(std::vector<T>& buffer, Access access) const;

            void unmap() const;

            template<typename T>
            void read(std::vector<T>& buffer, GLintptr start = 0, GLsizei end = -1) const;
        };
    }
}