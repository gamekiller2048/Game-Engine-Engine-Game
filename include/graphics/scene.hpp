#pragma once

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

        //virtual void keyCallback(const Event::KeyEvent& event);
        //virtual void mouseCallback(const Event::MouseEvent& event);
        virtual void windowSizeCallback(int w, int h);
        virtual void windowPosCallback(int x, int y);
        virtual void windowCloseCallback();
    };
}