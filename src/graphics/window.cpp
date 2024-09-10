#include <graphics/window.hpp>
#ifdef _WIN32
#include <graphics/win32/window.hpp>
#endif

#include <graphics/opengl/glcontext.hpp>

namespace mgl
{
	Window::Window(const std::string& title, uint width, uint height, RenderApi api) :
		title(title), size(width, height), api(api) {}

	void Window::createContext()
	{
		switch(api) {
		case RenderApi::OPENGL:
			context = createGLContext(this, 4, 3);
		}
	}

	void Window::setContext(const Ref<RenderContext>& context)
	{
		this->context = context;
	}

	Ref<RenderContext> Window::getContext() const
	{
		return context;
	}

	bool Window::isDestroyed() const
	{
		return destroyed;
	}

	void Window::addScene(const std::string& name, const Ref<Scene>& scene)
	{
		scenes[name] = scene;
		scene->name = name;
	}

	void Window::setScene(const std::string& name)
	{
		if(curScene)
			curScene->exit();

		curScene = scenes[name];
		curScene->enter();
	}

	Ref<Scene> Window::getScene() const
	{
		return curScene;
	}

	std::string Window::getTitle() const
	{
		return title;
	}

	int Window::getX() const
	{
		return pos.x;
	}

	int Window::getY() const
	{
		return pos.y;
	}

	mml::ivec2 Window::getPos() const
	{
		return pos;
	}

	uint Window::getWidth() const
	{
		return size.x;
	}

	uint Window::getHeight() const
	{
		return size.y;
	}

	mml::uvec2 Window::getSize() const
	{
		return size;
	}

	Ref<Window> createWindow(const std::string& title, uint width, uint height, RenderApi api)
	{
#ifdef _WIN32
		return CreateRef<win32::Window>(title, width, height, api);
#endif
	}
}