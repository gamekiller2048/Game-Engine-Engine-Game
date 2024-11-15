#pragma once
#include <math/math.hpp>
#include <graphics/window.hpp>

namespace mgl
{
    class Camera
    {
    public:
        mml::vec3 pos = mml::vec3(0);
        mml::vec3 orientation = mml::vec3(0, 0, 1);
        mml::vec3 up = mml::vec3(0, 1, 0);
        mml::mat4 view = mml::mat4(1);
        mml::mat4 projection = mml::mat4(1);
        mml::mat4 projView = mml::mat4(1);
    };
}
