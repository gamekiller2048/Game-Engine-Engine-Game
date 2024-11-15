#pragma once
#include <vector>
#include <numeric>
#include <glad/gl.h>
#include <graphics/render/mesh.hpp>
#include <graphics/opengl/vao.hpp>
#include <graphics/opengl/vbo.hpp>
#include <graphics/opengl/ebo.hpp>
#include <graphics/render/vertexlayout.hpp>

namespace mgl
{
    namespace gl
    {
        
        class Mesh : public mgl::Mesh
        {
        public:
            Mesh() = default;

            void create();
            void bind();

        protected:
            VAO vao;
            VBO vbo;
            EBO ebo;
        
            void setVertices(const void* vertices, const VertexLayout& vertexLayout, mgl::UsagePattern usage = mgl::UsagePattern::STATIC);
            void setIndices(const void* indices, int indicesPerElement = 1, mgl::UsagePattern usage = mgl::UsagePattern::STATIC);
            void updateVertices(const void* vertices, const VertexLayout& vertexLayout, size_t start = 0, size_t end = -1);
            void updateIndices(const void* indices, size_t start = 0, size_t end = -1, int indicesPerElement = 1);
        };
    }
}
