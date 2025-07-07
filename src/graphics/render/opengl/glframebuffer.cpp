#include <graphics/render/opengl/glframebuffer.hpp>
#include <graphics/render/opengl/gltexture2d.hpp>
#include <graphics/render/opengl/glcubemap.hpp>
#include "gltexture2dimpl.hpp"
#include "glcubemapimpl.hpp"
#include "glframebufferimpl.hpp"

namespace mgl
{
    static std::unordered_map<FrameBufferAttachmentType, gl::Attachment> glAttachmentMap = {
        {FrameBufferAttachmentType::COLOR, gl::Attachment::COLOR},
        {FrameBufferAttachmentType::DEPTH, gl::Attachment::DEPTH},
    };

    static std::unordered_map<FrameBufferAttachmentType, gl::BufferBit> glAttachmentToBufferBitMap = {
        {FrameBufferAttachmentType::COLOR, gl::BufferBit::COLOR},
        {FrameBufferAttachmentType::DEPTH, gl::BufferBit::DEPTH},
    };

    GLFrameBuffer::GLFrameBuffer(RenderContext* context) :
        FrameBuffer(context), impl(CreateOwned<GLFrameBufferImpl>())
    {
        impl->fbo.create();
    }

    GLFrameBuffer::~GLFrameBuffer() = default;

    GLFrameBufferImpl* GLFrameBuffer::getImpl() const
    {
        return impl.get();
    }

    void GLFrameBuffer::bind() const
    {
        impl->fbo.bind();
    }

    void GLFrameBuffer::unbind() const
    {
        impl->fbo.unbind();
    }

    void GLFrameBuffer::viewport(uint x, uint y, uint w, uint h) const
    {
        impl->fbo.viewport(x, y, w, h);
    }

    void GLFrameBuffer::clear(FrameBufferAttachmentType type) const
    {
        impl->fbo.clear(glAttachmentToBufferBitMap[type]);
    }

    void GLFrameBuffer::addRenderTarget(const Ref<Texture2D>& target, FrameBufferAttachment attachment, uint colorOutputLoc)
    {
        bind();

        impl->fbo.attachTexture(
            // TODO: don't explicitly downcast
            std::static_pointer_cast<GLTexture2D>(target)->getImpl()->texture,
            glAttachmentMap[attachment.type],
            attachment.index
        );

        if(attachment.type == FrameBufferAttachmentType::COLOR)
            colorOutputLocMap[colorOutputLoc] = (uint)glAttachmentMap[attachment.type] + attachment.index;
    }

    void GLFrameBuffer::addRenderTarget(const Ref<CubeMap>& target, FrameBufferAttachment attachment, uint colorOutputLoc)
    {
        bind();

        impl->fbo.attachTexture(
            // TODO: don't explicitly downcast
            std::static_pointer_cast<GLCubeMap>(target)->getImpl()->cubemap,
            glAttachmentMap[attachment.type],
            attachment.index
        );

        if(attachment.type == FrameBufferAttachmentType::COLOR)
            colorOutputLocMap[colorOutputLoc] = (uint)glAttachmentMap[attachment.type] + attachment.index;
    }
    
    void GLFrameBuffer::setShaderColorOutputLoc() const
    {
        std::vector<GLenum> outputs = {};
        std::unordered_map<uint, uint> outputLocMapCurr = colorOutputLocMap;

        if(colorOutputLocMap.size()) {
            uint outLoc = 0;
            while(outputLocMapCurr.size()) {
                auto it = outputLocMapCurr.find(outLoc);
                if(it != outputLocMapCurr.end()) {
                    outputs.push_back(it->second);
                    outputLocMapCurr.erase(it);
                }
                else
                    outputs.push_back(GL_NONE);
                outLoc++;
            }
        }
        else
            outputs = {GL_NONE};

        impl->fbo.setDrawAttachments(outputs);
    }
}