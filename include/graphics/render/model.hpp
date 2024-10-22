#pragma once
#include <vector>
#include <math/math.hpp>
#include <graphics/render/mesh.hpp>
#include <graphics/render/material.hpp>

namespace mgl
{
	class Model
	{
	public:
		Model() = default;

		void addMesh(Mesh&& mesh);

		Mesh& getMesh(uint index);
		const Mesh& getMesh(uint index) const;
		//const std::vector<Mesh> getMeshes() const;

		mml::mat4 getMatrix() const;

	private:
		mml::vec3 pos = mml::vec3(0);
		mml::vec3 rotate = mml::vec3(0);
		mml::vec3 scale = mml::vec3(1);
		std::vector<Mesh> meshes;
	};
}