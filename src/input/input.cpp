#include <input/input.hpp>

#ifdef _WIN32
#include <input/win32/input.hpp>
#endif

namespace mil
{
	mml::vec2 getMousePos()
	{
#ifdef _WIN32
		return win32::getMousePos();
#endif
	}

	bool isKeyPressed(Key key)
	{
#ifdef _WIN32
		return win32::isKeyPressed(key);
#endif
	}
	
	bool isMousePressed(Mouse button)
	{
#ifdef _WIN32
		return win32::isMousePressed(button);
#endif
	}
}