#pragma once
#include <random>
#include <math/math.hpp>

namespace mml
{
    namespace rng
    {
        int Int(int a, int b);
        float Float(float a, float b);
        float Random();
        mml::vec2 Vec2(float a, float b);
        mml::vec3 Vec3(float a, float b);
        mml::vec4 Vec4(float a, float b);
        void _init();
    };
}
