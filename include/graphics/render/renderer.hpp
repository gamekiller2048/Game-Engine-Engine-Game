#pragma once
#include <vector>
#include <graphics/render/renderscene.hpp>

namespace mgl
{
	class Renderer
	{
	public:
		virtual void render(const Ref<RenderScene>& scene) = 0;
	};

	Ref<Renderer> createRenderer();
}