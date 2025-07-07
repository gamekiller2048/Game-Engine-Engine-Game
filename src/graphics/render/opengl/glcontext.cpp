#include <graphics/render/opengl/glcontext.hpp>
#include "glcontextimpl.hpp"
#include <graphics/render/opengl/glvertexbuffer.hpp>
#include <graphics/render/opengl/glindexbuffer.hpp>
#include <graphics/render/opengl/glshaderprogram.hpp>
#include <graphics/render/opengl/gltexture2d.hpp>
#include <graphics/render/opengl/glcubemap.hpp>
#include <graphics/render/opengl/glframebuffer.hpp>

namespace mgl
{
    GLContext::GLContext() :
        impl(CreateOwned<GLContextImpl>()) {}

    GLContextImpl* GLContext::getImpl() const
    {
        return impl.get();
    }

    void GLContext::create(const Ref<Window>& window, uint major, uint minor, GLContextProfile profile)
    {
        useWindow(window);
        impl->context.create(major, minor, (gl::ContextProfile)profile);
    }

    void GLContext::makeCurrent()
    {
        impl->context.makeCurrent();
    }

    void GLContext::swapBuffers()
    {
        impl->context.swapBuffers();
    }

    void GLContext::clearColor() const
    {
        impl->context.clearColor();
    }
    
    void GLContext::clearDepth() const
    {
        impl->context.clearDepth();
    }

    void GLContext::setDepthTest(bool on) const
    {
        impl->context.setDepthTest(on);
    }

    void GLContext::setTransparency(bool on) const
    {
        impl->context.setTransparency(on);
    }

    void GLContext::setCulling(bool on) const
    {
        impl->context.setCulling(on);
    }

    void GLContext::viewport(uint x, uint y, uint w, uint h) const
    {
        impl->context.viewport(x, y, w, h);
    }

    Ref<VertexBuffer> GLContext::createVertexBuffer()
    {
        return CreateRef<GLVertexBuffer>(this);
    }

    Ref<IndexBuffer> GLContext::createIndexBuffer()
    {
        return CreateRef<GLIndexBuffer>(this);
    }

    Ref<ShaderProgram> GLContext::createShaderProgram()
    {
        return CreateRef<GLShaderProgram>(this);
    }

    Ref<Texture2D> GLContext::createTexture2D()
    {
        return CreateRef<GLTexture2D>(this);
    }

    Ref<CubeMap> GLContext::createCubeMap()
    {
        return CreateRef<GLCubeMap>(this);
    }

    Ref<FrameBuffer> GLContext::createFrameBuffer()
    {
        return CreateRef<GLFrameBuffer>(this);
    }
}