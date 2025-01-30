#pragma once
#include <math/math.hpp>
#include <graphics/render/shadow.hpp>

namespace mgl
{
    enum class LightType
    {
        DIRECTIONAL,
        POINT
    };

    class Light
    {
    public:
        mml::color color;
        float intensity;
        float specIntensity;

        Light(LightType type, const mml::color& color, float intensity, float specIntensity);
        virtual void use(const Ref<ShaderProgram>& shader, uint index) const = 0;

        virtual void createShadow(RenderContext* context, const mml::uvec2& size) = 0;
        virtual void useShadow() const = 0;

        virtual Ref<Shadow> getShadow() const = 0;

    protected:
        LightType type;
    };
}
