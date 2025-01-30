#include <graphics/render/opengl/glcontext.hpp>
#include "glcontextimpl.hpp"
#include <graphics/render/opengl/glvertexbuffer.hpp>
#include <graphics/render/opengl/glindexbuffer.hpp>
#include <graphics/render/opengl/glshaderprogram.hpp>
#include <graphics/render/opengl/gltexture2d.hpp>
#include <graphics/render/opengl/glcubemap.hpp>

namespace mgl
{
	GLContext::GLContext() :
		impl(CreateOwned<GLContextImpl>()) {}

	void GLContext::create(const Ref<Window>& window, uint major, uint minor, GLContextProfile profile)
	{
		useWindow(window);
		impl->context.create(major, minor, (gl::ContextProfile)profile);
	}

	void GLContext::makeCurrent()
	{
		impl->context.makeCurrent();
	}

	void GLContext::swapBuffers()
	{
		impl->context.swapBuffers();
	}

	void GLContext::clearColor() const
	{
		impl->context.clearColor();
	}
	
	void GLContext::clearDepth() const
	{
		impl->context.clearDepth();
	}

	Ref<VertexBuffer> GLContext::createVertexBuffer()
	{
		return CreateRef<GLVertexBuffer>(this);
	}

	Ref<IndexBuffer> GLContext::createIndexBuffer()
	{
		return CreateRef<GLIndexBuffer>(this);
	}

	Ref<ShaderProgram> GLContext::createShaderProgram()
	{
		return CreateRef<GLShaderProgram>(this);
	}

	Ref<Texture2D> GLContext::createTexture2D()
	{
		return CreateRef<GLTexture2D>(this);
	}

	Ref<CubeMap> GLContext::createCubeMap()
	{
		return CreateRef<GLCubeMap>(this);
	}
}