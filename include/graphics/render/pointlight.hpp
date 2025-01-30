#pragma once
#include <math/math.hpp>
#include <graphics/render/light.hpp>
#include <graphics/render/pointshadow.hpp>

namespace mgl
{
    class PointLight : public Light
    {
    public:
        mml::vec3 pos;
        float ambient;
        float a, b;

        PointLight(const mml::vec3& pos, const mml::color& color, float ambient=0.0f, float a=0.05f, float b=0.01f, float intensity=1, float specIntesity=0.00005f);
        void use(const Ref<ShaderProgram>& shader, uint index) const;

        void createShadow(RenderContext* context, const mml::uvec2& size);
        void useShadow() const;

        Ref<Shadow> getShadow() const;

    protected:
        Ref<PointShadow> shadow;
    };
}