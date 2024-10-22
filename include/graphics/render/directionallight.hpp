#pragma once
#include <math/math.hpp>
#include <graphics/render/light.hpp>
#include <graphics/opengl/shaderprogram.hpp>

namespace mgl
{
    class DirectionalLight : public Light
    {
    public:
        float ambient;
        mml::vec3 dir;

        DirectionalLight(const mml::vec3& dir, const mml::color& color, float ambient=0.0f, float specIntesity=0.5f);
        mml::mat4 getSpaceTransform();

    };
}