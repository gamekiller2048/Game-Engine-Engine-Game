#pragma once
#include <math/math.hpp>
#include <input/key.hpp>
#include <input/action.hpp>
#include <input/mousebutton.hpp>

namespace mil
{
    class KeyEvent
    {
    public:
        KeyEvent(Key key, Action action);

        Key key;
        Action action;
    };

    class MouseEvent
    {
    public:
        MouseEvent(Mouse button, Action action);

        Mouse button;
        Action action;
    };


    mml::vec2 getMousePos();
}
