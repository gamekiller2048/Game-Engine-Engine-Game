#pragma once
#include <graphics/render/indexbuffer.hpp>

namespace mgl
{
    class GLIndexBufferImpl;
    class GLIndexBuffer : public IndexBuffer
    {
    public:
        GLIndexBuffer(RenderContext* context);
        ~GLIndexBuffer();

        GLIndexBufferImpl* getImpl() const;

        void create();
        void bind() const;
        void unbind() const;

        void allocate(const void* buffer, uint size, BufferUsage usage) const;
        void write(const void* buffer, uint size, uint start = 0, uint end = -1) const;
        void read(const void* buffer, uint start = 0, uint end = -1) const;

    protected:
        Owned<GLIndexBufferImpl> impl;
    };
}
