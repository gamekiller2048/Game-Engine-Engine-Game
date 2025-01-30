#include <graphics/render/opengl/glcubemap.hpp>
#include "glcubemapimpl.hpp"

namespace mgl
{
	GLCubeMap::GLCubeMap(RenderContext* context) :
		CubeMap(context) {}

	GLCubeMap::~GLCubeMap() = default;

	void GLCubeMap::create()
	{
		impl->cubemap.create();
	}

	void GLCubeMap::bind()
	{
		impl->cubemap.bind();
	}

	void GLCubeMap::unbind()
	{
		impl->cubemap.unbind();
	}

	GLCubeMapImpl* GLCubeMap::getImpl() const
	{
		return impl.get();
	}
}