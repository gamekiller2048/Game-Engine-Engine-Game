#pragma once
#include <graphics/app.hpp>

namespace mgl
{
	namespace win32
	{
		class App : public mgl::App
		{
		public:
			void run();
			void destroy();
		};
	}
}