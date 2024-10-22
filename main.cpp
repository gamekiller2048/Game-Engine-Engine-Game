#include <glad/gl.h>
#include <graphics/window.hpp>
#include <graphics/app.hpp>
#include <graphics/scene.hpp>
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/geometry/shape2d.hpp>
#include <input/input.hpp>

class MyScene : public mgl::Scene
{
public:
	Ref<mgl::Window> window;
	mgl::gl::ShaderProgram shader;

	float i = 0.0f;
	
	MyScene(const Ref<mgl::Window>& window) :
		window(window)
	{
	}


	void foo(mml::ivec2 v)
	{

	}

	void keyCallback(const mil::KeyEvent& event)
	{
		if(event.action == mil::Action::PRESS) {
			std::cout << "Pressed";
		}
	}

	void update()
	{
		window->setTitle(mil::getMousePos().toString());

		if(mil::isKeyPressed(mil::Key::K_0)) {
			std::cout << "Asd";
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(mml::sin(i) * 0.5f + 0.5f, 1.0f, 0.0f, 1.0f);
		i += 0.001f;
	}
};

int main()
{
	Ref<mgl::App> app = mgl::createApp(mgl::RenderApi::OPENGL);
	Ref<mgl::Window> window = mgl::createWindow("hello world", 1000, 600);
	window->createContext();
	
	Ref<mgl::Scene> scene = CreateRef<MyScene>(window);
	window->addScene("main", scene);
	window->setScene("main");

	app->addWindow(window);
	app->run();
	return 0;
}