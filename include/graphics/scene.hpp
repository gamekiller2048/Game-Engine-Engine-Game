#pragma once
#include <input/event.hpp>

namespace mgl
{
    class Scene
    {
    public:
        std::string name;

        virtual ~Scene() = default;
        virtual void update() = 0;
        virtual void enter();
        virtual void exit();

        virtual void keyCallback(const mil::KeyEvent& event);
        virtual void mouseCallback(const mil::MouseEvent& event);
        virtual void windowSizeCallback(int w, int h);
        virtual void windowPosCallback(int x, int y);
        virtual void windowCloseCallback();
        virtual void lowLevelMsgLoopCallback(void* hWnd, unsigned int uMsg, unsigned int wParam, long lParam);
    };
}