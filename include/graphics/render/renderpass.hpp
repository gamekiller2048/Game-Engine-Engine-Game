#pragma once
#include <graphics/render/renderscene.hpp>

namespace mgl
{
	class RenderPass
	{
	public:
		virtual void render(const Ref<RenderScene>& scene) const = 0;
	};
}
