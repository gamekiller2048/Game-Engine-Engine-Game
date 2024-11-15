#include <graphics/render/renderscene.hpp>

namespace mgl
{
	RenderScene::RenderScene()
	{

	}

	void RenderScene::addMesh(const Ref<ModelMesh>& mesh)
	{
		meshes.push_back(mesh);
	}

	void RenderScene::addLight(const Ref<Light>& light)
	{
		lights.push_back(light);
	}

	void RenderScene::setCamera(const mgl::Ref<Camera>& camera)
	{
		this->camera = camera;
	}

	std::vector<Ref<ModelMesh>> RenderScene::getMeshes()
	{
		return meshes;
	}

	std::vector<Ref<Light>> RenderScene::getLights()
	{
		return lights;
	}

	mgl::Ref<Camera> RenderScene::getCamera()
	{
		return camera;
	}
}