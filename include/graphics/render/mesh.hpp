#pragma once
#include <vector>
#include <numeric>
#include <graphics/geometry/vertex.hpp>

namespace mgl
{
    enum class UsagePattern
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

    class Mesh
    {
    public:
        virtual void create() = 0;
        virtual void bind() = 0;

        template<typename T, typename U>
        void setGeometry(const Geometry<T, U>& geometry, int indicesPerElement = 1, UsagePattern usage = UsagePattern::STATIC);

        template<typename T>
        void setVertices(const std::vector<T>& vertices, UsagePattern usage = UsagePattern::STATIC);
        
        // indicesPerElement: when U is more then one component
        // e.g U = Triange{a, b, c}, indicesPerElement=3
        template<typename U>
        void setIndices(const std::vector<U>& indices, int indicesPerElement = 1, UsagePattern usage = UsagePattern::STATIC);
        
        template<typename T, typename U>
        void updateGeometry(const Geometry<T, U>& geometry, size_t start = 0, size_t end = -1, int indicesPerElement = 1);
        
        template<typename T>
        void updateVertices(const std::vector<T>& vertices, size_t start = 0, size_t end = -1);
        
        template<typename U>
        void updateIndices(const std::vector<U>& indices, size_t start = 0, size_t end = -1, int indicesPerElement = 1);
    
    protected:
        uint vertexCount = 0;
        uint indiceCount = 0;

        virtual void setVertices(const void* vertices, const VertexLayout& vertexLayout, UsagePattern usage = UsagePattern::STATIC) = 0;
        virtual void setIndices(const void* indices, int indicesPerElement = 1, UsagePattern usage = UsagePattern::STATIC) = 0;
        virtual void updateVertices(const void* vertices, const VertexLayout& vertexLayout, size_t start = 0, size_t end = -1) = 0;
        virtual void updateIndices(const void* indices, size_t start = 0, size_t end = -1, int indicesPerElement = 1) = 0;
    };

    Ref<Mesh> createMesh();

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
        setVertices(vertices.data(), vertices[0].vertexLayout(), usage);
    }

    template<typename U>
    void Mesh::setIndices(const std::vector<U>& indices, int indicesPerElement, UsagePattern usage)
    {
        indiceCount = indices.size() * indicesPerElement;
        setIndices(indices.data(), indicesPerElement, usage);
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
        updateVertices(vertices.data(), vertices[0].vertexLayout(), start, end);
    }

    template<typename U>
    void Mesh::updateIndices(const std::vector<U>& indices, size_t start, size_t end, int indicesPerElement)
    {
        updateIndices(indices.data(), start, end, indicesPerElement);
    }
}