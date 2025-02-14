#pragma once
#include <graphics/render/renderscene.hpp>

namespace mgl
{
	class GeometryPass
	{
	public:
		virtual void render(const Ref<RenderScene>& scene) const = 0;
	};

	class LightingPass
	{
	public:
		virtual void render(const Ref<RenderScene>& scene) const = 0;
	};

	//class RenderPass
	//{
	//public:
	//	RenderPass(const Ref<GeometryPass>& geometryPass, const Ref<LightingPass>& lightingPass);
	//	virtual void render(const Ref<RenderScene>& scene) const = 0;

	//protected:
	//	Ref<GeometryPass> geometryPass;
	//	Ref<LightingPass> lightingPass;

	//};
}
