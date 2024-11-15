#include <glad/gl.h>
#include <input/input.hpp>
#include <graphics/window.hpp>
#include <graphics/app.hpp>
#include <graphics/scene.hpp>
#include <graphics/geometry/shape2d.hpp>
#include <graphics/opengl/context.hpp>
#include <graphics/render/model.hpp>
#include <graphics/render/mesh.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/geometry/shape3d.hpp>
#include <graphics/render/renderer.hpp>
#include <graphics/camera/firstperson.hpp>
#include <math/random.hpp>

class MyScene : public mgl::Scene
{
public:
	Ref<mgl::Window> window;
	Ref<mgl::Renderer> renderer;
	Ref<mgl::gl::Context> context;
	Ref<mgl::Model> model;
	mgl::FirstPersonCamera camera;
	Ref<mgl::BasicMaterial> material;

	float i = 0.0f;
	
	MyScene(const Ref<mgl::Window>& window, const Ref<mgl::gl::Context>& context, const Ref<mgl::Renderer>& renderer) :
		window(window), context(context), renderer(renderer)
	{
		context->makeCurrent();
		context->setDepthTest(true);

		model = CreateRef<mgl::Model>();
		Ref<mgl::Mesh> mesh = mgl::createMesh();
		mesh->create();
		mesh->setGeometry(mgl::gl::Shape3D().Cube());

		material = CreateRef<mgl::BasicMaterial>();

		model->setMesh(mesh);
		model->setMaterial(material);
	}

	void keyCallback(const mil::KeyEvent& event)
	{
		if(event.action == mil::Action::PRESS) {
		}
	}

	void mouseCallback(const mil::MouseEvent& event)
	{
	}

	void windowPosCallback(int x, int y)
	{
	}

	void update()
	{
		context->clearColor();
		context->clearDepth();
		glViewport(0, 0, window->getWidth(), window->getHeight());

		window->setTitle(mil::getMousePos().toString());

		if(mil::isKeyPressed(mil::Key::K_0)) {
			std::cout << "Asd";
		}

		i += 0.001f;
		material->color = mml::color(mml::sin(i) * 0.5f + 1, mml::cos(i) * 0.5f + 1, 0, 1);
		model->setScale(mml::vec3(model->getScale().x + mml::cos(i * 10.0f) / 1000));

		camera.BasicFirstPersonView(window);
		camera.calculate();
		camera.perspective(45.0f, 0.1f, 1000.0f, window->getSize());
		
		renderer->render(model, &camera);
	}
};

int main()
{
	Ref<mgl::App> app = CreateRef<mgl::App>(mgl::RenderApi::OPENGL);
	Ref<mgl::Window> window = CreateRef<mgl::Window>("hello world", 1000, 600);
	Ref<mgl::gl::Context> context = CreateRef<mgl::gl::Context>(window.get(), 4, 3);
	window->setContext(context);
	
	Ref<mgl::Renderer> renderer = mgl::createRenderer();

	Ref<mgl::Scene> scene = CreateRef<MyScene>(window, context, renderer);
	window->addScene("main", scene);
	window->setScene("main");

	app->addWindow(window);
	app->run();
	return 0;
}