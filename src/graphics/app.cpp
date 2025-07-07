#include <graphics/app.hpp>

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
}