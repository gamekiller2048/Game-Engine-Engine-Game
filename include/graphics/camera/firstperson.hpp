#pragma once
#include <graphics/camera/perspective.hpp>
#include <graphics/window.hpp>

namespace mgl
{
    class FirstPersonCamera : public PerspectiveCamera
    {
    public:
        bool lockMouse = true;
        float speed = 0.1f;
        float sensitivity = 2;
        mml::vec3 vel = mml::vec3(0);

        void BasicFirstPersonView(const Ref<mgl::Window>& window);
    };
}