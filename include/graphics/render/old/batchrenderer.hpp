#pragma once
#include <vector>
#include <array>
#include <graphics/render/mesh.hpp>
#include <graphics/opengl/shader.hpp>
#include <graphics/geometry/vertex.hpp>

namespace mgl
{
    template<typename T>
    class BatchRenderer
    {
    public:
        void create();
        void alloc(GLuint numVertices, GLuint numIndices);
        void update();
        void add(const std::vector<T>& vertices, const std::vector<GLuint>& indices);
        void draw(const ShaderProgram& shader) const;

        ModelMesh* getMesh();
    
    private:
        std::vector<T> vertices;
        std::vector<GLuint> indices;

        ModelMesh mesh;
    };

    template<typename T>
    void BatchRenderer<T>::create()
    {
        mesh.create();
    }

    template<typename T>
    void BatchRenderer<T>::alloc(GLuint numVertices, GLuint numIndices)
    {
        vertices.reserve(numVertices);
        indices.reserve(numIndices);
    }

    template<typename T>
    void BatchRenderer<T>::update()
    {
        mesh.setGeometry(Geometry<T, GLuint>{vertices, indices}, 1, UsagePattern::STATIC_DRAW);
        //mesh.updateGeometry(Geometry<T, GLuint>{vertices, indices});
    }

    template<typename T>
    void BatchRenderer<T>::add(const std::vector<T>& vertices, const std::vector<GLuint>& indices)
    {
        uint vertIndexRelZero = this->vertices.size();
        std::copy(vertices.begin(), vertices.end(), std::back_inserter(this->vertices));

        for(int i=0; i < indices.size(); i++)
            this->indices.push_back(indices[i] + vertIndexRelZero);
    }

    template<typename T>
    void BatchRenderer<T>::draw(const ShaderProgram& shader) const
    {
        mesh.draw(shader);
    }

    template<typename T>
    ModelMesh* BatchRenderer<T>::getMesh()
    {
        return &mesh;
    }
}
