#include <graphics/render/opengl/renderer.hpp>
#include <graphics/render/shaderprogram.hpp>

namespace mgl
{
	namespace gl
	{
		void Renderer::render(const Ref<Model>& model, const Camera* camera)
		{
			Ref<mgl::ShaderProgram> shader = model->getMaterial()->shader;

			shader->bind();
			model->getMaterial()->use();
			shader->uniform("projection", camera->projView);

			model->getMesh()->bind();
		}
	}
}