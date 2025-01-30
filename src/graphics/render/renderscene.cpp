#include <graphics/render/renderscene.hpp>

namespace mgl
{
	std::vector<Ref<Model>> RenderScene::getModels() const
	{
		return models;
	}

	std::vector<Ref<Light>> RenderScene::getLights() const
	{
		return lights;
	}

	Ref<Camera> RenderScene::getCamera() const
	{
		return camera;
	}

	mml::uvec2 RenderScene::getSize() const
	{
		return size;
	}

	void RenderScene::addModel(const Ref<Model>& model)
	{
		models.push_back(model);
	}

	void RenderScene::addLight(const Ref<Light>& light)
	{
		lights.push_back(light);
	}

	void RenderScene::setCamera(const Ref<Camera>& camera)
	{
		this->camera = camera;
	}

	void RenderScene::setSize(const mml::uvec2& size)
	{
		this->size = size;
	}
}