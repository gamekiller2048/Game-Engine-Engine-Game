#include <input/event.hpp>
#include <input/action.hpp>
#include <input/mousebutton.hpp>

namespace mil
{
    KeyEvent::KeyEvent(Key key, Action action) :
        key(key), action(action) {}

    MouseEvent::MouseEvent(Mouse button, Action action) :
        button(button), action(action) {}
}
