#pragma once
#include <resourceloader/resourceloader.hpp>
#include <graphics/render/modelmesh.hpp>

namespace mrl
{
	struct ModelData
	{
		std::vector<mgl::Ref<mgl::ModelMesh>> meshes;
	};

	struct ObjMesh
	{
		std::string name;
		mgl::Ref<mgl::ModelMesh> mesh;
		std::vector<mgl::Vertex3DUVN> vertices;
		std::vector<GLuint> indices;
	};

	struct ObjModelData
	{
		std::vector<mgl::Ref<ObjMesh>> meshes;
	};

	class ModelLoader : ResourceLoader
	{
	public:
		static ModelData load(const std::string& filePath);
		static ObjModelData loadObj(const std::string& filePath);
	};
}