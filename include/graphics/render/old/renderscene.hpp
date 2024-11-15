#pragma once
#include <graphics/render/modelmesh.hpp>
#include <graphics/core/resource.hpp>
#include <graphics/render/light.hpp>
#include <graphics/render/material.hpp>
#include <graphics/camera/camera.hpp>

namespace mgl
{
	class RenderScene
	{
	public:
		RenderScene();
		void addMesh(const Ref<ModelMesh>& mesh);
		void addLight(const Ref<Light>& light);
		void setCamera(const mgl::Ref<Camera>& camera);

		std::vector<Ref<ModelMesh>> getMeshes();
		std::vector<Ref<Light>> getLights();
		mgl::Ref<Camera> getCamera();

	private:
		std::vector<Ref<ModelMesh>> meshes;
		std::vector<Ref<Light>> lights;

		mgl::Ref<Camera> camera;
	};
}