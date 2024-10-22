#pragma once
#include <numeric>
#include <graphics/render/mesh.hpp>

namespace mgl
{
    class MeshInstanced : public Mesh
    {
    public:
        GLuint instanceCount = 0;

        void create();

        template<typename T>
        void setInstances(const std::vector<T>& instances, UsagePattern usage=UsagePattern::STATIC_DRAW);

        template<typename T>
        void updateInstances(const std::vector<T>& instances, GLsizei start=0, GLsizei end=-1);

        void draw(const ShaderProgram& shader) const;

    protected:
        VBO instancedVBO;
    };

    template<typename T>
    void MeshInstanced::setInstances(const std::vector<T>& instances, UsagePattern usage)
    {
        instanceCount = instances.size();

        vao.bind();
        instancedVBO.allocate(instances, usage);

        if(!instanceCount) return;

        GLuint offset = 0;
        for(const VBI& vbi : instances[0].structure()) {
            vao.linkAttrib(instancedVBO, vbi.layout, vbi.components, vbi.type, sizeof(T), offset);
            glVertexAttribDivisor(vbi.layout, 1);
            offset += vbi.components * sizeof(vbi.type);
        }
    }

    template<typename T>
    void MeshInstanced::updateInstances(const std::vector<T>& instances, GLsizei start, GLsizei end)
    {
        vao.bind();
        instancedVBO.write(instances, start, end);

        GLuint offset = 0;
        for(VBI vbi : instances[0].structure()) {
            vao.linkAttrib(instancedVBO, vbi.layout, vbi.components, vbi.type, sizeof(T), offset);
            glVertexAttribDivisor(vbi.layout, 1);
            offset += vbi.components * sizeof(vbi.type);
        }
    }
}
