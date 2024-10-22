#pragma once
#include <math/math.hpp>
#include <graphics/render/light.hpp>
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/render/pointshadow.hpp>

namespace mgl
{
    class PointLight : public Light
    {
    public:
        mml::vec3 pos;
        float ambient;
        float a, b;

        PointLight(const mml::vec3& pos, const mml::color& color, float ambient=0.0f, float a=0.05f, float b=0.01f, float specIntesity=0.00005f);
    };
}