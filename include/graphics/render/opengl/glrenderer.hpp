#pragma once
#include <graphics/render/renderer.hpp>
#include <graphics/render/renderscene.hpp>

namespace mgl
{
	class GLRenderer : public Renderer
	{
	public:
		GLRenderer();
		~GLRenderer();

		void render(const Ref<RenderScene>& scene);
	};
}