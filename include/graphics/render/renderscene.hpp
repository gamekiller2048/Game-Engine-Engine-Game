#pragma once
#include <vector>
#include <graphics/render/model.hpp>
#include <graphics/render/light.hpp>
#include <graphics/render/material.hpp>
#include <graphics/camera/camera.hpp>
#include <common/typealias.hpp>

namespace mgl
{
	class RenderScene
	{
	public:
		std::vector<Ref<Model>> getModels() const;
		std::vector<Ref<Light>> getLights() const;
		Ref<Camera> getCamera() const;
		mml::uvec2 getSize() const;

		void addModel(const Ref<Model>& model);
		void addLight(const Ref<Light>& light);
		void setCamera(const Ref<Camera>& camera);
		void setSize(const mml::uvec2& size);

	protected:
		std::vector<Ref<Model>> models;
		std::vector<Ref<Light>> lights;
		Ref<Camera> camera;

		mml::uvec2 size;
	};
}