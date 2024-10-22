#include <graphics/render/mesh.hpp>

namespace mgl
{
    void Mesh::create()
    {
        vbo.create();
        ebo.create();
        vao.create();
    }

    void Mesh::draw(const ShaderProgram& shader) const
    {
        vao.bind();

        if(indiceCount == 0)
            shader.drawArrays(RenderPrimative::TRIANGLES, 0, vertexCount);
        else
            shader.drawElements(RenderPrimative::TRIANGLES, indiceCount);
    }
}
