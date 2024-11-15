#pragma once
#include <memory>
#include <math/math.hpp>
#include <graphics/core/resource.hpp>
#include <graphics/opengl/shaderprogram.hpp>
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
        float specIntensity;
        LightType type;
        bool shadows = false;
        Ref<Shadow> shadow;

        Light(LightType type, const mml::color& color, float specIntensity);
    };
}
