#pragma once
#include <graphics/render/framebuffer.hpp>
#include <unordered_map>

namespace mgl
{
    class GLFrameBufferImpl;
    class GLFrameBuffer : public FrameBuffer
    {
    public:
        GLFrameBuffer(RenderContext* context);
        ~GLFrameBuffer();

        void bind() const;
        void unbind() const;
        
        GLFrameBufferImpl* getImpl() const;

        void viewport(uint x, uint y, uint w, uint h) const;
        void clear(FrameBufferAttachmentType type) const;
        void addRenderTarget(const Ref<Texture2D>& target, FrameBufferAttachment attachment, uint colorOutputLoc=0);
        void addRenderTarget(const Ref<CubeMap>& target, FrameBufferAttachment attachment, uint colorOutputLoc=0);
        void setShaderColorOutputLoc() const;

    protected:
        Owned<GLFrameBufferImpl> impl;
        uint numColorAttachments = 0;
        std::unordered_map<uint, uint> colorOutputLocMap;
    };
}