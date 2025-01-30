#pragma once
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
	class Texture2D
	{
	public:
		Texture2D(RenderContext* context);

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void loadFromFile(const std::string& filePath) = 0;
		virtual void allocate(uint width, uint height) = 0;
	
	protected:
		RenderContext* context;
	};
}