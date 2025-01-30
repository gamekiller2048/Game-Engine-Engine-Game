#include <graphics/render/opengl/glrenderer.hpp>
#include <graphics/render/model.hpp>
#include <graphics/render/light.hpp>

namespace mgl
{
	GLRenderer::GLRenderer()
	{
	}

	GLRenderer::~GLRenderer()
	{
	}

	void GLRenderer::render(const Ref<RenderScene>& scene)
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

					model->getMesh()->bind();
					glDrawElements(GL_TRIANGLES, 3 * 800, GL_UNSIGNED_INT, 0);
				}

				shadow->endFrame();
			}
			
			
			//gl::Context::getCurrent().lock()->viewport(0, 0, scene->getSize().x, scene->getSize().y);

			for(const Ref<Model>& model : scene->getModels()) {
				Ref<mgl::ShaderProgram> shader = model->getMaterial()->shader;
				shader->bind();
				shader->uniform("u_projection", scene->getCamera()->projView);
				shader->uniform("u_transform", model->getTransform());

				light->use(shader, 0);
				model->getMaterial()->use();
				model->getMesh()->draw(shader);
			}
		}
	}
}