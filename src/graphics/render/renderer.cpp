#include <graphics/render/renderer.hpp>
#include <graphics/app.hpp>

namespace mgl
{
	void ForwardRenderPass::render(const Ref<RenderScene>& scene) const
	{
		for(const Ref<Model>& model : scene->getModels()) {
			Ref<mgl::ShaderProgram> shader = model->getMaterial()->shader;
			shader->bind();
			shader->uniform("u_projection", scene->getCamera()->projView);
			shader->uniform("u_transform", model->getTransform());

			for(int i = 0; i < scene->getLights().size(); i++)
				scene->getLights()[i]->use(shader, i);

			model->getMaterial()->use();
			model->getMesh()->draw(shader);
		}
	}

	void ShadowRenderPass::render(const Ref<RenderScene>& scene) const
	{
		for(const Ref<Light>& light : scene->getLights()) {
			if(light->getShadow()) {
				Ref<Shadow> shadow = light->getShadow();
				Ref<mgl::ShaderProgram> shader = shadow->getShader();

				shader->bind();
				light->useShadow();
				shadow->startFrame();

				for(const Ref<Model>& model : scene->getModels()) {
					shader->uniform("u_transform", model->getTransform());
					model->getMesh()->draw(shader);
				}

				shadow->endFrame();
			}
		}
	}

	void Renderer::render(const Ref<RenderScene>& scene) const
	{
		for(const Ref<RenderPass>& renderPass : renderPasses)
			renderPass->render(scene);
	}
}