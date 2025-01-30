#pragma once
#include <vector>
#include <numeric>
#include <graphics/geometry/vertex.hpp>
#include <graphics/render/vertexbuffer.hpp>
#include <graphics/render/indexbuffer.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
    class Mesh
    {
    public:
        Mesh(RenderContext* context);

        void bind();
        void draw(const Ref<ShaderProgram>& shader);

        // indicesPerElement: when U is more then one component
        // e.g U = Triange{a, b, c}, indicesPerElement=3
        template<typename T, typename U>
        void setGeometry(const Geometry<T, U>& geometry, int indicesPerElement = 1, BufferUsage usage = BufferUsage::STATIC);

        template<typename T>
        void setVertices(const std::vector<T>& vertices, BufferUsage usage = BufferUsage::STATIC);
        
        template<typename U>
        void setIndices(const std::vector<U>& indices, int indicesPerElement = 1, BufferUsage usage = BufferUsage::STATIC);
        
        template<typename T, typename U>
        void updateGeometry(const Geometry<T, U>& geometry, size_t start = 0, size_t end = -1, int indicesPerElement = 1);
        
        template<typename T>
        void updateVertices(const std::vector<T>& vertices, size_t start = 0, size_t end = -1);
        
        template<typename U>
        void updateIndices(const std::vector<U>& indices, size_t start = 0, size_t end = -1, int indicesPerElement = 1);
    
    protected:
        uint vertexCount = 0;
        uint indiceCount = 0;
        
        Ref<VertexBuffer> vertexBuffer;
        Ref<IndexBuffer> indexBuffer;
    };

    template<typename T, typename U>
    void Mesh::setGeometry(const Geometry<T, U>& geometry, int indicesPerElement, BufferUsage usage)
    {
        setVertices(geometry.vertices, usage);
        setIndices(geometry.indices, indicesPerElement, usage);
    }

    template<typename T>
    void Mesh::setVertices(const std::vector<T>& vertices, BufferUsage usage)
    {
        vertexCount = vertices.size();
        vertexBuffer->bind();
        vertexBuffer->allocate(vertices.data(), vertexCount * sizeof(T), usage);
        
        if(vertexCount)
            vertexBuffer->setLayout(vertices[0].vertexLayout());
    }

    template<typename U>
    void Mesh::setIndices(const std::vector<U>& indices, int indicesPerElement, BufferUsage usage)
    {
        indiceCount = indices.size() * indicesPerElement;
        indexBuffer->bind();
        indexBuffer->allocate(indices.data(), indiceCount * sizeof(U), usage);
    }

    template<typename T, typename U>
    void Mesh::updateGeometry(const Geometry<T, U>& geometry, size_t start, size_t end, int indicesPerElement)
    {
        updateVertices(geometry.vertices, start, end);
        updateIndices(geometry.indices, indicesPerElement, start, end);
    }

    template<typename T>
    void Mesh::updateVertices(const std::vector<T>& vertices, size_t start, size_t end)
    {
        vertexBuffer->write(vertices.data(), vertexCount * sizeof(T), start, end);
    }

    template<typename U>
    void Mesh::updateIndices(const std::vector<U>& indices, size_t start, size_t end, int indicesPerElement)
    {
        indexBuffer->write(indices.data(), indices.size() * sizeof(U), start, end);
    }
}