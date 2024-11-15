#include <graphics/camera/firstperson.hpp>
#include <math/transform.hpp>
#include <input/input.hpp>

namespace mgl
{
    void FirstPersonCamera::BasicFirstPersonView(const Ref<Window>& window)
    {
        // pos
        if(mil::isKeyPressed(mil::Key::K_W))
            pos += speed * orientation;
        if(mil::isKeyPressed(mil::Key::K_S))
            pos += speed * -orientation;
        if(mil::isKeyPressed(mil::Key::K_A))
            pos += speed * -mml::normalize(orientation.cross(up));
        if(mil::isKeyPressed(mil::Key::K_D))
            pos += speed * mml::normalize(orientation.cross(up));
        if(mil::isKeyPressed(mil::Key::K_SPACE))
            pos += speed * up;
        if(mil::isKeyPressed(mil::Key::K_LEFT_SHIFT))
            pos += speed * -up;

        // lock/unlock mouse pos
        if(mil::isKeyPressed(mil::Key::K_ESCAPE)) {
            lockMouse = false;
        }
        else if(mil::isKeyPressed(mil::Key::K_TAB)) {
            lockMouse = true;
            window->setMousePos(mml::vec2(window->getWidth() / 2.0f, window->getHeight() / 2.0f));
        }


        if(lockMouse) {
            mml::vec2 mouse = window->getMousePos();

            float rotatex = sensitivity * (float)(mouse.y - mml::floor(window->getHeight() / 2.0f)) / window->getHeight();
            float rotatey = sensitivity * (float)(mouse.x - mml::floor(window->getWidth() / 2.0f)) / window->getWidth();

            mml::vec3 orientationX = mml::rotate(orientation, rotatex * mml::normalize(orientation.cross(up)));
            if(mml::abs(mml::acos(orientationX.normalize().dot(up.normalize())) - mml::radians(90.0f)) <= mml::radians(85.0f))
                orientation = orientationX;

            orientation = mml::rotate(orientation, rotatey * up);
            window->setMousePos(mml::vec2(window->getWidth() / 2.0f, window->getHeight() / 2.0f));
        }
    }
}