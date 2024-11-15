#include <graphics/render/modelmesh.hpp>

namespace mgl
{
    void ModelMesh::setMaterial(const Ref<Material>& material)
    {
        this->material = material;
    }

    const Ref<Material> ModelMesh::getMaterial() const
    {
        return material;
    }

    void ModelMesh::setTransform(const mml::mat4& transform)
    {
        this->transform = transform;
    }

    mml::mat4 ModelMesh::getTransform() const
    {
        return transform;
    }

}