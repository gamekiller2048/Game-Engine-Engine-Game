#include <graphics/render/opengl/gltexture2d.hpp>
#include "gltexture2dimpl.hpp"
#include <graphics/opengl/context.hpp>
#include <unordered_map>

namespace mgl
{
	static std::unordered_map<TextureFormat, gl::Format> formatMap = {
		{TextureFormat::RGB, gl::Format::RGB},
		{TextureFormat::RGBA, gl::Format::RGBA},
		{TextureFormat::DEPTH, gl::Format::DEPTH}
	};

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

	void GLTexture2D::uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const
	{
		shader->uniform(loc, (int)impl->texture.getUnit());
	}

	void GLTexture2D::loadFromFile(const std::string& filePath) const
	{
		gl::Context* context = gl::Context::getCurrent();
		GLuint unit = context->getUnusedTexUnit();
		context->consumeTexUnit(unit);
		impl->texture.loadFromFile(filePath, unit);
	}

	void GLTexture2D::allocate(uint width, uint height, TextureFormat format) const
	{
		gl::Context* context = gl::Context::getCurrent();
		GLuint unit = context->getUnusedTexUnit();
		context->consumeTexUnit(unit);
		impl->texture.allocate(width, height, formatMap[format], formatMap[format], gl::Primative::FLOAT, unit);
	}
}