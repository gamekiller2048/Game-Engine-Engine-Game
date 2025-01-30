#pragma once
#include <graphics/render/shadow.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/texture2d.hpp>
#include <graphics/camera/orthographic.hpp>

namespace mgl
{
    class DirectionalShadow : public Shadow
    {
    public:
        DirectionalShadow(float bias=0.0005f, int sampleRadius=2);

        void create(const mml::uvec2& size);
        Ref<gl::Texture2D> getMap() const;
        Ref<ShaderProgram> getShader() const;
    
    protected:
        Ref<gl::Texture2D> map;
        Ref<OrthographicCamera> camera;
    };
}
