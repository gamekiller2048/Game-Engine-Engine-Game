#include <graphics/render/opengl/glvertexbuffer.hpp>
#include "glvertexbufferimpl.hpp"
#include <unordered_map>

namespace mgl
{
    static std::unordered_map<BufferUsage, gl::UsagePattern> glUsageMap = {
        {BufferUsage::STATIC, gl::UsagePattern::STATIC_DRAW},
        {BufferUsage::DYNAMIC, gl::UsagePattern::DYNAMIC_DRAW},
        {BufferUsage::STREAM, gl::UsagePattern::STREAM_DRAW}
    };

    GLVertexBuffer::GLVertexBuffer(RenderContext* context) :
        VertexBuffer(context), impl(CreateOwned<GLVertexBufferImpl>()) {}

    GLVertexBuffer::~GLVertexBuffer() = default;

    GLVertexBufferImpl* GLVertexBuffer::getImpl() const
    {
        return impl.get();
    }

    void GLVertexBuffer::setLayout(const VertexLayout& layout)
    {
        GLuint offset = 0;
        for(const VertexLayoutAttribute& attrib : layout.attributes) {
            impl->vao.linkAttrib(impl->vbo, attrib.layout, attrib.components, (gl::Primative)attrib.type, layout.size, offset);
            offset += attrib.size;
        }
    }

    void GLVertexBuffer::create()
    {
        impl->vao.create();
        impl->vao.bind();
        impl->vbo.create();
    }

    void GLVertexBuffer::bind() const
    {
        impl->vao.bind();
        impl->vbo.bind();
    }

    void GLVertexBuffer::unbind() const
    {
        impl->vbo.unbind();
    }

    void GLVertexBuffer::allocate(const void* buffer, size_t size, BufferUsage usage) const
    {
        impl->vbo.allocate(buffer, size, glUsageMap[usage]);
    }
    
    void GLVertexBuffer::write(const void* buffer, size_t size, uint start, uint end) const
    {
        impl->vbo.write(buffer, size, size, end == -1 ? -1 : end);
    }
    
    void GLVertexBuffer::read(const void* buffer, size_t start, uint end) const
    {
        //impl->vbo.read(buffer, start, end == -1 ? -1 : end);
    }
}
