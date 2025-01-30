#pragma once
#include <graphics/render/buffer.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(RenderContext* context);
    };
}
