#include <graphics/render/opengl/glindexbuffer.hpp>
#include "glindexbufferimpl.hpp"
#include <unordered_map>

namespace mgl
{
    static std::unordered_map<BufferUsage, gl::UsagePattern> glUsageMap = {
        {BufferUsage::STATIC, gl::UsagePattern::STATIC_DRAW},
        {BufferUsage::DYNAMIC, gl::UsagePattern::DYNAMIC_DRAW},
        {BufferUsage::STREAM, gl::UsagePattern::STREAM_DRAW}
    };

    GLIndexBuffer::GLIndexBuffer(RenderContext* context) :
        IndexBuffer(context), impl(CreateOwned<GLIndexBufferImpl>())
    {
        impl->ebo.create();
    }

    GLIndexBuffer::~GLIndexBuffer() = default;

    GLIndexBufferImpl* GLIndexBuffer::getImpl() const
    {
        return impl.get();
    }

    void GLIndexBuffer::bind() const
    {
        impl->ebo.bind();
    }

    void GLIndexBuffer::unbind() const
    {
        impl->ebo.unbind();
    }

    void GLIndexBuffer::allocate(const void* buffer, uint size, BufferUsage usage) const
    {
        impl->ebo.allocate(buffer, size, glUsageMap[usage]);
    }

    void GLIndexBuffer::write(const void* buffer, uint size, uint start, uint end) const
    {
        impl->ebo.write(buffer, size, start, end == -1 ? -1 : end);
    }

    void GLIndexBuffer::read(const void* buffer, uint start, uint end) const
    {
        //impl->ebo.read(buffer, start, end == -1 ? -1 : end);
    }
}
