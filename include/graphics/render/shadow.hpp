#pragma once
#include <graphics/render/rendercontext.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/opengl/fbo.hpp>
#include <graphics/camera/camera.hpp>

namespace mgl
{
    class Light;
    class Shadow
    {
    public:
        RenderContext* context;
        mml::uvec2 size;
        float bias;
        int sampleRadius;

        Shadow(RenderContext* context, float bias, int sampleRadius);

        virtual void create(const mml::uvec2& size) = 0;
        void startFrame() const;
        void endFrame() const;

        virtual Ref<Camera> getCamera() const = 0;
        virtual Ref<ShaderProgram> getShader() const = 0;

    protected:
        gl::FBO fbo;
    };
}
