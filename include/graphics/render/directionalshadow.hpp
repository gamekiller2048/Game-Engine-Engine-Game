#pragma once
#include <graphics/render/shadow.hpp>
#include <graphics/render/texture2d.hpp>
#include <graphics/camera/orthographic.hpp>

namespace mgl
{
    class DirectionalShadow : public Shadow
    {
    public:
        DirectionalShadow(RenderContext* context, float bias=0.005f, int sampleRadius=2);

        void create(const mml::uvec2& size);
        Ref<Texture2D> getMap() const;
        Ref<ShaderProgram> getShader() const;
        Ref<Camera> getCamera() const;
    
    protected:
        Ref<Texture2D> map;
        Ref<OrthographicCamera> camera;
    };
}
