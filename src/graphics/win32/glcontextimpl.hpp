#pragma once
#include <Windows.h>

namespace mgl
{
	class GLContextImpl
	{
	public:
		HGLRC hRC;
		HDC hDC;
	};
}