#pragma once
#include <vector>
#include <graphics/render/renderscene.hpp>
#include <graphics/render/renderpass.hpp>

namespace mgl
{
	class ForwardRenderPass : public RenderPass
	{
	public:
		void render(const Ref<RenderScene>& scene) const;
	};
	
	class ShadowRenderPass : public RenderPass
	{
	public:
		void render(const Ref<RenderScene>& scene) const;
	};

	class Renderer
	{
	public:
		std::vector<Ref<RenderPass>> renderPasses;
		void render(const Ref<RenderScene>& scene) const;
	};
}