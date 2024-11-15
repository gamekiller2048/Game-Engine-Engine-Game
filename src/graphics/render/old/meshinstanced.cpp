#include <graphics/render/meshinstanced.hpp>

namespace mgl
{
    void MeshInstanced::create()
    {
        vbo.create();
        ebo.create();
        vao.create();
        instancedVBO.create();
    }

    void MeshInstanced::draw(const ShaderProgram& shader) const
    {
        vao.bind();

        if(indiceCount == 0)
            shader.drawArraysInstanced(RenderPrimative::TRIANGLES, 0, vertexCount, instanceCount);
        else
            shader.drawElementsInstanced(RenderPrimative::TRIANGLES, indiceCount, instanceCount);
    }
}
