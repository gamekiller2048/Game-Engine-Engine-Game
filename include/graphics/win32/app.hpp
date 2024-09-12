#pragma once
#include <graphics/app.hpp>

namespace mgl
{
	namespace win32
	{
		class App : public mgl::App
		{
		public:
			App(RenderApi api);

			void run();
			void destroy();
		};
	}
}