#include <graphics/app.hpp>

#ifdef _WIN32
#include <graphics/win32/app.hpp>
#endif

namespace mgl
{
	App::App(RenderApi api) :
		api(api) 
	{
		instance = this;
	}

	void App::addWindow(const Ref<Window>& window)
	{
		windows.push_back(window);
	}

	RenderApi App::getRenderApi() const
	{
		return api;
	}

	void App::setRenderApi(RenderApi api)
	{
		this->api = api;
	}

	App* App::getInstance()
	{
		return App::instance;
	}

	Ref<App> createApp(RenderApi api)
	{
#ifdef _WIN32
		return CreateRef<win32::App>(api);
#endif
	}
}