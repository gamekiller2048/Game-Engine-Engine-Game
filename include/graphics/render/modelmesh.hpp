#pragma once
#include <graphics/render/mesh.hpp>
#include <graphics/render/material.hpp>
#include <graphics/core/resource.hpp>
#include <math/math.hpp>

namespace mgl
{
	class ModelMesh : public Mesh
	{
	public:
		void setMaterial(const Ref<Material>& material);
		const Ref<Material> getMaterial() const;

		void setTransform(const mml::mat4& transform);
		mml::mat4 getTransform() const;

	private:
		Ref<Material> material;
		mml::mat4 transform = mml::mat4(1);
	};
}