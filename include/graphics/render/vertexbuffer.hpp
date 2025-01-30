#pragma once
#include <graphics/render/buffer.hpp>
#include <graphics/render/rendercontext.hpp>
#include <graphics/render/vertexlayout.hpp>

namespace mgl
{
    class VertexBuffer : public Buffer
    {
    public:
        VertexBuffer(RenderContext* context);

        virtual void setLayout(const VertexLayout& layout) const = 0;
    };
}