#include <graphics/render/model.hpp>
#include <math/transform.hpp>

namespace mgl
{
	mml::mat4 Model::getMatrix() const
	{
		return mml::translate(mml::scale(mml::rotate(mml::mat4(1), rotate), scale), pos);
	}

	void Model::addMesh(Mesh&& mesh)
	{
		meshes.push_back(std::move(mesh));
	}

	Mesh& Model::getMesh(uint index)
	{
		return meshes[index];
	}

	//const std::vector<Mesh> Model::getMeshes() const
	//{
	//	return meshes;
	//}
}