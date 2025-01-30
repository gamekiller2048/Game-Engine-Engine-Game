#include <graphics/render/opengl/gltexture2d.hpp>
#include "gltexture2dimpl.hpp"
#include <graphics/opengl/context.hpp>

namespace mgl
{
	GLTexture2D::GLTexture2D(RenderContext* context) :
		Texture2D(context), impl(CreateOwned<GLTexture2DImpl>())
	{
		impl->texture.create();
	}

	GLTexture2D::~GLTexture2D() = default;

	GLTexture2DImpl* GLTexture2D::getImpl() const
	{
		return impl.get();
	}

	void GLTexture2D::bind() const
	{
		impl->texture.bind();
	}

	void GLTexture2D::unbind() const
	{
		impl->texture.unbind();
	}

	void GLTexture2D::loadFromFile(const std::string& filePath)
	{
		gl::Context* context = gl::Context::getCurrent();
		GLuint unit = context->getUnusedTexUnit();
		context->consumeTexUnit(unit);
		impl->texture.loadFromFile(filePath, unit);
	}

	void GLTexture2D::allocate(uint width, uint height)
	{
		gl::Context* context = gl::Context::getCurrent();
		GLuint unit = context->getUnusedTexUnit();
		context->consumeTexUnit(unit);
		//impl->texture.allocate(width, height);
	}
}