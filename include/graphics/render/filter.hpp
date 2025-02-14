#pragma once
#include <graphics/render/renderpass.hpp>
#include <graphics/render/framebuffer.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <array>

namespace mgl
{
	class Filter
	{
	public:
		Filter(RenderContext* context, const mml::uvec2 size);
		Ref<Texture2D> apply(const Ref<Texture2D>& input) const;

	protected:
		Ref<FrameBuffer> framebuffer;
		Ref<Texture2D> output;
		Ref<ShaderProgram> shader;
		Ref<Mesh> quad;
	};

	class ConvolutionFilter : public Filter
	{
	public:
		ConvolutionFilter(RenderContext* context, const std::array<float, 9>& kernel, const mml::uvec2 size);
	
	protected:
		std::array<float, 9> kernel;
	};

	class BlurFilter : public ConvolutionFilter
	{
	public:
		BlurFilter(RenderContext* context, const mml::uvec2 size);
	};

	class SharpenFilter : public ConvolutionFilter
	{
	public:
		SharpenFilter(RenderContext* context, const mml::uvec2 size);
	};

	class EdgeFilter : public ConvolutionFilter
	{
	public:
		EdgeFilter(RenderContext* context, const mml::uvec2 size);
	};
}