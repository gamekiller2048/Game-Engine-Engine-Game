#pragma once
#include <vector>
#include <numeric>
#include <glad/gl.h>
#include <graphics/opengl/vao.hpp>
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/ebo.hpp>
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/geometry/vertex.hpp>

namespace mgl
{
    class Mesh
    {
    public:
        Mesh() = default;

        GLuint vertexCount = 0;
        GLuint indiceCount = 0;

        void create();

        template<typename T, typename U>
        void setGeometry(const Geometry<T, U>& geometry, int indicesPerElement=1, UsagePattern usage=UsagePattern::STATIC_DRAW);

        template<typename T>
        void setVertices(const std::vector<T>& vertices, UsagePattern usage=UsagePattern::STATIC_DRAW);

        template<typename T>
        void setIndices(const std::vector<T>& indices, int indicesPerElement=1, UsagePattern usage=UsagePattern::STATIC_DRAW);

        template<typename T, typename U>
        void updateGeometry(const Geometry<T, U>& geometry, GLsizei start=0, GLsizei end=-1, int indicesPerElement=1);

        template<typename T>
        void updateVertices(const std::vector<T>& vertices, GLsizei start=0, GLsizei end=-1);

        template<typename T>
        void updateIndices(const std::vector<T>& indices, GLsizei start=0, GLsizei end=-1, int indicesPerElement=1);

        void draw(const ShaderProgram& shader) const;

    protected:
        VAO vao;
        VBO vbo;
        EBO ebo;
    };

    template<typename T, typename U>
    void Mesh::setGeometry(const Geometry<T, U>& geometry, int indicesPerElement, UsagePattern usage)
    {
        setVertices(geometry.vertices, usage);
        setIndices(geometry.indices, indicesPerElement, usage);
    } 

    template<typename T>
    void Mesh::setVertices(const std::vector<T>& vertices, UsagePattern usage)
    {
        vertexCount = vertices.size();

        vao.bind();
        vbo.allocate(vertices, usage);

        if(!vertexCount) return;

        GLuint offset = 0;
        for(const VBI& vbi : vertices[0].structure()) {
            vao.linkAttrib(vbo, vbi.layout, vbi.components, vbi.type, sizeof(T), offset);
            offset += vbi.components * sizeof(vbi.type);
        }
    }

    template<typename T>
    void Mesh::setIndices(const std::vector<T>& indices, int indicesPerElement, UsagePattern usage)
    {
        indiceCount = indices.size() * indicesPerElement;

        vao.bind();
        ebo.allocate(indices, usage);
    }

    template<typename T, typename U>
    void Mesh::updateGeometry(const Geometry<T, U>& geometry, GLsizei start, GLsizei end, int indicesPerElement)
    {
        updateVertices(geometry.vertices, start, end);
        updateIndices(geometry.indices, indicesPerElement, start, end);
    }

    template<typename T>
    void Mesh::updateVertices(const std::vector<T>& vertices, GLsizei start, GLsizei end)
    {
        vao.bind();
        vbo.write(vertices, start, end);

        GLuint offset = 0;
        for(const VBI& vbi : vertices[0].structure()) {
            vao.linkAttrib(vbo, vbi.layout, vbi.components, vbi.type, sizeof(T), offset);
            offset += vbi.components * sizeof(vbi.type);
        }
    }

    template<typename T>
    void Mesh::updateIndices(const std::vector<T>& indices, GLsizei start, GLsizei end, int indicesPerElement)
    {
        vao.bind();
        ebo.write(indices, start, end);
    }
}
