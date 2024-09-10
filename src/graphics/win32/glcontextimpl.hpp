#pragma once
#include <Windows.h>

namespace mgl
{
	namespace win32
	{
		class GLContextImpl
		{
		public:
			HGLRC hRC;
			HDC hDC;
		};
	}
}