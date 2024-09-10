#include <graphics/scene.hpp>

namespace mgl
{
    void Scene::enter()
    {
        MLL_DEBUG(mll::Info("", "Entering scene \"" + name + "\" (default method)"));
    }

    void Scene::exit()
    {
        MLL_DEBUG(mll::Info("", "Entering scene \"" + name + "\" (default method)"));
    }

    //void Scene::keyCallback(const Event::KeyEvent& event) {}
    //void Scene::mouseCallback(const Event::MouseEvent& event) {}
    void Scene::windowSizeCallback(int w, int h) {}
    void Scene::windowPosCallback(int x, int y) {}
    void Scene::windowCloseCallback() {}
}