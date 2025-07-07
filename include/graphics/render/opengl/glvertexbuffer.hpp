#pragma once
#include <graphics/render/vertexbuffer.hpp>

namespace mgl
{
    class GLVertexBufferImpl;
    class GLVertexBuffer : public VertexBuffer
    {
    public:
        GLVertexBuffer(RenderContext* context);
        ~GLVertexBuffer();

        GLVertexBufferImpl* getImpl() const;
        void setLayout(const VertexLayout& layout) const;
        
        void bind() const;
        void unbind() const;

        void allocate(const void* buffer, size_t size, BufferUsage usage) const;
        void write(const void* buffer, size_t size, uint start = 0, uint end = -1) const;
        void read(const void* buffer, size_t start = 0, uint end = -1) const;

    protected:
        Owned<GLVertexBufferImpl> impl;
    };
}
