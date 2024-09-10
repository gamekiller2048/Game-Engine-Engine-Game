#include <graphics/app.hpp>
#ifdef _WIN32
#include <graphics/win32/app.hpp>
#endif

namespace mgl
{
	void App::addWindow(const Ref<Window>& window)
	{
		windows.push_back(window);
	}

	Ref<App> createApp()
	{
#ifdef _WIN32
		return CreateRef<win32::App>();
#endif
	}
}