#pragma once
#include <vector>
#include <graphics/render/renderscene.hpp>
#include <graphics/render/renderpass.hpp>
#include <graphics/render/filter.hpp>

namespace mgl
{
	class ForwardLightingPass : public LightingPass
	{
	public:
		void render(const Ref<RenderScene>& scene) const;
	};

	class ShadowGeometryPass : public GeometryPass
	{
	public:
		void render(const Ref<RenderScene>& scene) const;
	};

	class DeferredGeometryPass : public GeometryPass
	{
	public:
		DeferredGeometryPass(RenderContext* context, const mml::uvec2& size);
		void render(const Ref<RenderScene>& scene) const;

	protected:
		Ref<FrameBuffer> framebuffer;
		Ref<Texture2D> position;
		Ref<Texture2D> normal;
		Ref<Texture2D> albeodoSpecular;

		friend class DeferredLightingPass;
	};

	class DeferredLightingPass : public LightingPass
	{
	public:
		DeferredLightingPass(RenderContext* context, const Ref<DeferredGeometryPass>& geometryPass);
		void render(const Ref<RenderScene>& scene) const;

	protected:
		Ref<DeferredGeometryPass> geometryPass;
		Ref<ShaderProgram> shader;
		Ref<Mesh> quad;
	};

	class Renderer
	{
	public:
		std::vector<Ref<GeometryPass>> geometryPasses;
		std::vector<Ref<LightingPass>> lightingPasses;
		std::vector<Ref<Filter>> filters;
		
		Renderer(RenderContext* context, const mml::uvec2& size);
		void render(const Ref<RenderScene>& scene) const;
	
	protected:
		Ref<FrameBuffer> framebuffer;
		Ref<Texture2D> renderOutput;
		Ref<ShaderProgram> shader;
		Ref<Mesh> quad;
	};
}