#include <input/win32/input.hpp>
#include <common/win32/errors.hpp>
#include <Windows.h>
#include "../../common/win32/errorcheck.hpp"

namespace mil
{
    namespace win32
    {
        mml::vec2 getMousePos()
        {
            POINT p;
            WIN_CALL(GetCursorPos, &p);
            return mml::vec2((float)p.x, (float)p.y);
        }

        bool isKeyPressed(Key key)
        {
            return WIN_CALLR(GetKeyState, (int)key) & 0x8000;
        }

        bool isMousePressed(Mouse button)
        {
            return WIN_CALLR(GetKeyState, (int)button) & 0x8000;
        }

    }
}