#pragma once
#include <graphics/render/rendercontext.hpp>
#include <graphics/render/vertexbuffer.hpp>
#include <graphics/render/indexbuffer.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/texture2d.hpp>
#include <graphics/render/cubemap.hpp>
#include <graphics/render/framebuffer.hpp>

namespace mgl
{
    enum class GLContextProfile
    {
        CORE,
        COMPATABILITY
    };

    class GLContextImpl;
    class GLContext : public RenderContext
    {
    public:
        GLContext();

        GLContextImpl* getImpl() const;
        void create(const Ref<Window>& window, uint major, uint minor, GLContextProfile profile = GLContextProfile::CORE);
        void useWindow(const Ref<Window>& window);
        void makeCurrent();
        void swapBuffers();
        bool isCurrent() const;
        bool isWindowUsed(const Ref<Window>& window) const;

        void clearColor() const;
        void clearDepth() const;
        void setDepthTest(bool on) const;
        void setTransparency(bool on) const;
        void setCulling(bool on) const;
        void viewport(uint x, uint y, uint w, uint h) const;

        Ref<VertexBuffer> createVertexBuffer();
        Ref<IndexBuffer> createIndexBuffer();
        Ref<ShaderProgram> createShaderProgram();
        Ref<Texture2D> createTexture2D();
        Ref<CubeMap> createCubeMap();
        Ref<FrameBuffer> createFrameBuffer();
    
    protected:
        Owned<GLContextImpl> impl;
    };
}