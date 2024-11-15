#pragma once
#include <math/math.hpp>
#include <graphics/render/mesh.hpp>
#include <graphics/render/material.hpp>

namespace mgl
{
	class Model
	{
	public:
		Ref<Mesh> getMesh() const;
		Ref<Material> getMaterial() const;

		void setMesh(const Ref<Mesh>& mesh);
		void setMaterial(const Ref<Material>& material);
		void setPos(const mml::vec3& pos);
		void setRotate(const mml::vec3& rotate);
		void setScale(const mml::vec3& scale);
		void setTransform(const mml::mat4& transform);

	protected:
		Ref<Mesh> mesh;
		Ref<Material> material;

		mml::vec3 pos = mml::vec3(0);
		mml::vec3 rotate = mml::vec3(0);
		mml::vec3 scale = mml::vec3(1);
		mml::mat4 transform = mml::mat4(1);
	
		mml::mat4 calculateTransform();
	};
}