#pragma once
#include <graphics/render/shadow.hpp>
#include <graphics/render/cubemap.hpp>
#include <graphics/camera/perspective.hpp>

namespace mgl
{
    class PointShadow : public Shadow
    {
    public:
        float farPlane = 100;

        PointShadow(RenderContext* context, float bias=0.0005f, int sampleRadius=2);
        
        void create(const mml::uvec2& size);
        Ref<ShaderProgram> getShader() const;
        Ref<Camera> getCamera() const;

    protected:
        Ref<CubeMap> cubemap;
        Ref<PerspectiveCamera> camera;
    };
}