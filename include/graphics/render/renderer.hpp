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

	class DeferredGeometryRenderPass : public RenderPass
	{
	public:
		DeferredGeometryRenderPass(RenderContext* context, const mml::uvec2& size);
		void render(const Ref<RenderScene>& scene) const;

	protected:
		Ref<ShaderProgram> shader;
		Ref<FrameBuffer> framebuffer;
		Ref<Texture2D> position;
		Ref<Texture2D> normal;
		Ref<Texture2D> albeodoSpecular;

		friend class DeferredRenderPass;
	};

	class DeferredLightingRenderPass : public RenderPass
	{
	public:
		DeferredLightingRenderPass(RenderContext* context);
		void render(const Ref<RenderScene>& scene) const;

	protected:
		Ref<ShaderProgram> shader;
		Ref<Mesh> quad;

		friend class DeferredRenderPass;
	};

	class DeferredRenderPass : public RenderPass
	{
	public:
		DeferredRenderPass(RenderContext* context, const mml::uvec2& size);
		void render(const Ref<RenderScene>& scene) const;

	protected:
		DeferredGeometryRenderPass geometryPass;
		DeferredLightingRenderPass lightingPass;
	};

	class Renderer
	{
	public:
		std::vector<Ref<RenderPass>> renderPasses;
		void render(const Ref<RenderScene>& scene) const;
	};
}