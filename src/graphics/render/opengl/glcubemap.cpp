#include <graphics/render/opengl/glcubemap.hpp>
#include "glcubemapimpl.hpp"
#include <graphics/opengl/context.hpp>
#include <unordered_map>

namespace mgl
{
	static std::unordered_map<TextureFormat, gl::Format> formatMap = {
		{TextureFormat::RGB, gl::Format::RGB},
		{TextureFormat::RGBA, gl::Format::RGBA},
		{TextureFormat::DEPTH, gl::Format::DEPTH}
	};

	GLCubeMap::GLCubeMap(RenderContext* context) :
		CubeMap(context), impl(CreateOwned<GLCubeMapImpl>())
	{
		impl->cubemap.create();
	}

	GLCubeMap::~GLCubeMap() = default;

	GLCubeMapImpl* GLCubeMap::getImpl() const
	{
		return impl.get();
	}

	void GLCubeMap::bind() const
	{
		impl->cubemap.bind();
	}

	void GLCubeMap::unbind() const
	{
		impl->cubemap.unbind();
	}

	void GLCubeMap::bindUnit() const
	{
		impl->cubemap.setActiveUnit();
	}

	void GLCubeMap::uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const
	{
		shader->uniform(loc, (int)impl->cubemap.getUnit());
	}

	void GLCubeMap::loadFromFile(const std::string& filePath) const
	{
		gl::Context* context = gl::Context::getCurrent();
		GLuint unit = context->getUnusedTexUnit();
		context->consumeTexUnit(unit);
		//impl->cubemap.loadFromFile(filePath, unit);
	}

	void GLCubeMap::allocate(uint width, uint height, TextureFormat format) const
	{
		gl::Context* context = gl::Context::getCurrent();
		GLuint unit = context->getUnusedTexUnit();
		context->consumeTexUnit(unit);
		impl->cubemap.allocate(width, height, formatMap[format], formatMap[format], gl::Primative::FLOAT, unit);
	}
}