#pragma once
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
    enum class BufferUsage
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

    class Buffer
    {
    public:
        Buffer(RenderContext* context);

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void allocate(const void* buffer, uint size, BufferUsage usage) const = 0;
        virtual void write(const void* buffer, uint size, uint start = 0, uint end = -1) const = 0;
        virtual void read(const void* buffer, uint start = 0, uint end = -1) const = 0;
    
    protected:
        RenderContext* context;
    };
}
