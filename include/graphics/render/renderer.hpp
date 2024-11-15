#pragma once
#include <vector>
#include <graphics/render/model.hpp>
#include <graphics/camera/camera.hpp>

namespace mgl
{
	class Renderer
	{
	public:
		virtual void render(const Ref<Model>& model, const Camera* camera) = 0;
	};

	Ref<Renderer> createRenderer();
}