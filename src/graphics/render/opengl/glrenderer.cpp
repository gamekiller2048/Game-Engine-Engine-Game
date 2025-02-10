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
					model->getMesh()->draw(shader);
				}

				shadow->endFrame();
			}	
		}
	}
}