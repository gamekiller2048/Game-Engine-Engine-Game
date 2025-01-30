#pragma once
#include <math/math.hpp>
#include <graphics/render/light.hpp>
#include <graphics/render/directionalshadow.hpp>

namespace mgl
{
    class DirectionalLight : public Light
    {
    public:
        float ambient;
        mml::vec3 dir;

        DirectionalLight(const mml::vec3& dir, const mml::color& color, float ambient=0.0f, float intensity=1, float specIntesity=0.5f);
        void use(const Ref<ShaderProgram>& shader, uint index) const;
        
        void createShadow(RenderContext* context, const mml::uvec2& size);
        void useShadow() const;
        
        Ref<Shadow> getShadow() const;
        mml::mat4 getLightProjection() const;

    protected:
        Ref<DirectionalShadow> shadow;
    };
}