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
			shader->uniform("transform", model->getTransform());

			model->getMesh()->bind();

			//shader->drawElements(mgl::gl::RenderPrimative::TRIANGLES, 36);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
	}
}