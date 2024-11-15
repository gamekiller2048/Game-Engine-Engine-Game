#include <graphics/render/opengl/mesh.hpp>
#include <unordered_map>

namespace mgl
{
    namespace gl
    {
        static const std::unordered_map<mgl::UsagePattern, UsagePattern> usagePatternTable
        {
            {mgl::UsagePattern::STATIC, UsagePattern::STATIC_DRAW},
            {mgl::UsagePattern::DYNAMIC, UsagePattern::DYNAMIC_DRAW},
            {mgl::UsagePattern::STREAM, UsagePattern::STREAM_DRAW}
        };

        void Mesh::create()
        {
            vbo.create();
            ebo.create();
            vao.create();
        }

        void Mesh::bind()
        {
            vao.bind();
        }

        void Mesh::setVertices(const void* vertices, const VertexLayout& vertexLayout, mgl::UsagePattern usage)
        {
            vao.bind();
            vbo.allocate(vertices, vertexCount * vertexLayout.size, usagePatternTable.at(usage));

            if(!vertexCount) return;

            GLuint offset = 0;
            for(const VertexLayoutAttribute& attrib : vertexLayout.attributes) {
                vao.linkAttrib(vbo, attrib.layout, attrib.components, (Primative)attrib.type, vertexLayout.size, offset);
                offset += attrib.size;
            }
        }

        void Mesh::setIndices(const void* indices, int indicesPerElement, mgl::UsagePattern usage)
        {
            vao.bind();
            ebo.allocate(indices, indiceCount * sizeof(GLuint), usagePatternTable.at(usage));
        }

        void Mesh::updateVertices(const void* vertices, const VertexLayout& vertexLayout, size_t start, size_t end)
        {
            vao.bind();
            vbo.write(vertices, vertexCount * vertexLayout.size, start, end);

            GLuint offset = 0;
            for(const VertexLayoutAttribute& attrib : vertexLayout.attributes) {
                vao.linkAttrib(vbo, attrib.layout, attrib.components, (Primative)attrib.type, vertexLayout.size, offset);
                offset += attrib.size;
            }
        }

        void Mesh::updateIndices(const void* indices, size_t start, size_t end, int indicesPerElement)
        {
            vao.bind();
            ebo.write(indices, indiceCount * sizeof(GLuint), start, end);
        }
    }
}
