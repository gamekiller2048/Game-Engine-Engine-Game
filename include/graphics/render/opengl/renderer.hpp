#pragma once
#include <graphics/render/renderer.hpp>
#include <graphics/render/model.hpp>
#include <graphics/camera/camera.hpp>

namespace mgl
{
	namespace gl
	{
		class Renderer : public mgl::Renderer
		{
		public:
			void render(const Ref<Model>& model, const Camera* camera);
		};

	}
}