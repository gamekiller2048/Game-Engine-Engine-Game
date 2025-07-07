#pragma once
#include <graphics/camera/camera.hpp>

namespace mgl
{
    class OrthographicCamera : public Camera
    {
    public:
        float right, left, bottom, top, near, far;

        void orthographic(float right, float left, float bottom, float top, float near, float far);
        void calculate();
    };
}