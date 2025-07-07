#pragma once
#include <graphics/camera/camera.hpp>

namespace mgl
{
    class PerspectiveCamera : public Camera
    {
    public:
        float fov, near, far = 0;
        mml::uvec2 size;

        void perspective(float fov, float near, float far, const mml::uvec2& size);
        void calculate();
    };
}