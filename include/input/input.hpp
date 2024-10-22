#pragma once
#include <math/math.hpp>
#include <input/key.hpp>
#include <input/mousebutton.hpp>

namespace mil
{
	mml::vec2 getMousePos();
	bool isKeyPressed(Key key);
	bool isMousePressed(Mouse button);
}