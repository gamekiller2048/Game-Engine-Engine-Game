#pragma once
#include <glad/gl.h>
#include <vector>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/enums.hpp>
#include "errorcheck.hpp"

namespace mgl
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

	enum class UsagePattern : GLuint
	{
		STATIC_DRAW = GL_STATIC_DRAW,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		STREAM_DRAW = GL_STREAM_DRAW,
		STATIC_READ = GL_STATIC_READ,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		STREAM_READ = GL_STREAM_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_COPY = GL_DYNAMIC_COPY,
		STREAM_COPY = GL_STREAM_COPY,

	};

	struct VBI
	{
		GLuint layout;
		GLuint components;
		Primative type;
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

		template<typename T>
		void allocate(const std::vector<T>& buffer, UsagePattern usage) const;

		template<typename T>
		void allocate(GLsizei bytes, UsagePattern usage) const;

		template<typename T>
		void write(const std::vector<T>& buffer, GLintptr start=0, GLsizei end=-1) const;

		template<typename T>
		void* map(std::vector<T>& buffer, Access access) const;

		void unmap() const;

		template<typename T>
		void read(std::vector<T>& buffer, GLintptr start=0, GLsizei end=-1) const;
	};

	template<typename T>
	void Buffer::allocate(const std::vector<T>& buffer, UsagePattern usage) const
	{
		bind();
		GL_CALL(glBufferData, gltype, buffer.size() * sizeof(T), buffer.data(), (GLenum)usage);
	}

	template<typename T>
	void Buffer::allocate(GLsizei bytes, UsagePattern usage) const
	{
		bind();
		GL_CALL(glBufferData, gltype, bytes, nullptr, (GLenum)usage);
	}

	template<typename T>
	void Buffer::write(const std::vector<T>& buffer, GLintptr start, GLsizei end) const
	{
		bind();
		GL_CALL(glBufferSubData, gltype, start, end == -1 ? end : buffer.size() * sizeof(T), buffer.data());
	}

	template<typename T>
	void* Buffer::map(std::vector<T>& buffer, Access access) const
	{
		bind();
		return GL_CALLV(glMapBuffer, gltype, (GLenum)access);
	}

	template<typename T>
	void Buffer::read(std::vector<T>& buffer, GLintptr start, GLsizei end) const
	{
		bind();
		GL_CALL(glGetBufferSubData, gltype, start, end == -1 ? end : buffer.size() * sizeof(T), buffer.data());
	}
}