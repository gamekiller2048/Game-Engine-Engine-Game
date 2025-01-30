#pragma once
#include <graphics/render/texture2d.hpp>
#include <graphics/render/cubemap.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
	enum class FrameBufferAttachmentType
	{
		DEPTH,
		COLOR
	};

	class FrameBufferAttachment
	{
	public:
		FrameBufferAttachmentType type;
		uint index;
	};

	class FrameBuffer
	{
	public:
		FrameBuffer(RenderContext* context);

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void viewport(uint x, uint y, uint w, uint h) const = 0;
		virtual void clear(FrameBufferAttachmentType type) const = 0;
		virtual void addRenderTarget(const Ref<Texture2D>& target, FrameBufferAttachment attachment, uint outputLoc) = 0;
		virtual void addRenderTarget(const Ref<CubeMap>& target, FrameBufferAttachment attachment, uint outputLoc) = 0;
		virtual void setShaderOutputLocations() const = 0;

	protected:
		RenderContext* context;
	};
}