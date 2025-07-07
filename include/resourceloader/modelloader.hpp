#pragma once
#include <vector>
#include <resourceloader/resourceloader.hpp>
#include <graphics/render/model.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mrl
{
    struct ModelData
    {
        std::vector<Ref<mgl::Model>> meshes;
    };

    struct ObjMeshData
    {
        std::string name;
        std::vector<mgl::gl::Vertex3DUVN> vertices;
        std::vector<GLuint> indices;
    };

    struct ObjModelData
    {
        std::vector<ObjMeshData> meshes;
    };

    class ModelLoader : ResourceLoader
    {
    public:
        static ModelData load(const std::string& filePath);
        static ObjModelData loadObj(const std::string& filePath);
    };
}