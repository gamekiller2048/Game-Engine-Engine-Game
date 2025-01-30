#pragma once
#include <Windows.h>

namespace mgl
{
	namespace gl
	{
		class ContextImpl
		{
		public:
			HGLRC hRC;
			HDC hDC;
		};
	}
}