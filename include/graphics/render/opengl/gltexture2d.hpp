#pragma once
#include <graphics/render/texture2d.hpp>
#include <graphics/render/shaderprogram.hpp>

namespace mgl
{
	class GLTexture2DImpl;
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(RenderContext* context);
		~GLTexture2D();

		GLTexture2DImpl* getImpl() const;
		
		void create();
		void bind() const;
		void unbind() const;
		void loadFromFile(const std::string& filePath);
		void allocate(uint width, uint height);

	protected:
		Owned<GLTexture2DImpl> impl;
	};
}