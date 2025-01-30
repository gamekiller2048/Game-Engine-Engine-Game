#include <graphics/render/shadow.hpp>
#include <graphics/render/model.hpp>
#include <graphics/opengl/context.hpp>

namespace mgl
{
	Shadow::Shadow(RenderContext* context, float bias, int sampleRadius) :
		context(context), bias(bias), sampleRadius(sampleRadius) {}

	void Shadow::startFrame() const
	{
		framebuffer->bind();
		framebuffer->setShaderOutputLocations();
		framebuffer->viewport(0, 0, size.x, size.y);
		framebuffer->clear(FrameBufferAttachmentType::DEPTH);
	}

	void Shadow::endFrame() const
	{
		framebuffer->unbind();
	}
}