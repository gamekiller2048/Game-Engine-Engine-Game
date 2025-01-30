#include <graphics/render/shadow.hpp>
#include <graphics/render/model.hpp>
#include <graphics/opengl/context.hpp>

namespace mgl
{
	Shadow::Shadow(RenderContext* context, float bias, int sampleRadius) :
		context(context), bias(bias), sampleRadius(sampleRadius) {}

	void Shadow::startFrame() const
	{
		fbo.bind();
		//gl::Context::getCurrent().lock()->viewport(0, 0, size.x, size.y);
		fbo.clear(gl::BufferBit::DEPTH);
	}

	void Shadow::endFrame() const
	{
		fbo.unbind();
	}
}