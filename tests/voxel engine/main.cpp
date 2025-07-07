#include <input/input.hpp>
#include <graphics/window.hpp>
#include <graphics/app.hpp>
#include <graphics/scene.hpp>
#include <graphics/geometry/shape2d.hpp>
#include <graphics/render/opengl/glcontext.hpp>
#include <graphics/render/model.hpp>
#include <graphics/render/mesh.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/texture2d.hpp>
#include <graphics/render/renderer.hpp>
#include <graphics/camera/firstperson.hpp>
#include <graphics/render/renderscene.hpp>
#include <graphics/render/directionallight.hpp>
#include <graphics/render/shadervariant.hpp>
#include "mesher.hpp"
#include "chunk.hpp"

class MyScene : public mgl::Scene
{
public:
	Ref<mgl::Window> window;
	Ref<mgl::Renderer> renderer;
	Ref<mgl::RenderContext> context;
	Ref<mgl::FirstPersonCamera> camera;
	Ref<mgl::DirectionalLight> light;
	Ref<mgl::RenderScene> renderScene;
	Ref<mgl::Model> model;

	MyScene(const Ref<mgl::Window>& window) :
		window(window)
	{
		context = window->getContext();
		context->setDepthTest(true);

		renderer = CreateRef<mgl::Renderer>(context.get(), window->getSize());
		Ref<mgl::DeferredGeometryPass> pass = CreateRef<mgl::DeferredGeometryPass>(context.get(), window->getSize());

		renderer->geometryPasses.push_back(pass);
		renderer->lightingPasses.push_back(CreateRef<mgl::DeferredLightingPass>(context.get(), pass));

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
		//glFrontFace(GL_CCW);

		Ref<mgl::Mesh> mesh = context->createMesh();

		
		VE::Chunk chunk;
		chunk.generate();
		VE::Mesher mesher(&chunk);

		mgl::Geometry<VE::BlockVertex, GLuint> geometry = mesher.greedyMesh();
		
		std::cout << "vertices: " << geometry.vertices.size();
		mesh->setGeometry(geometry);

		model = CreateRef<mgl::Model>();
		model->setMesh(mesh);
		model->setMaterial(CreateRef<mgl::StandardMaterial>(context.get(), mgl::StandardShaderVairant(mgl::RenderPipeline::DEFERRED, false, false, false, 0, 1)));
		
		renderScene = CreateRef<mgl::RenderScene>();
		camera = CreateRef<mgl::FirstPersonCamera>();

		light = CreateRef<mgl::DirectionalLight>(mml::vec3(1, 1, 1), mml::color(1, 0, 0, 1));
		renderScene->addLight(light);
		renderScene->setCamera(camera);
		renderScene->addModel(model);
	}

	void update()
	{
		glClearColor(0.1, 0.1, 0.3, 1);
		context->clearColor();
		context->clearDepth();
		context->viewport(0, 0, window->getWidth(), window->getHeight());

		window->setTitle(mil::getMousePos().toString());
		camera->BasicFirstPersonView(window);
		camera->calculate();
		camera->perspective(45.0f, 0.1f, 1000.0f, window->getSize());
		
		renderScene->setSize(window->getSize());
		renderer->render(renderScene);
	}
};

int main()
{
	Ref<mgl::App> app = CreateRef<mgl::App>(mgl::RenderApi::OPENGL);
	Ref<mgl::Window> window = CreateRef<mgl::Window>("hello world", 1000, 600);
	
	Ref<mgl::GLContext> context = CreateRef<mgl::GLContext>();
	context->create(window, 3, 3);
	window->setContext(context);

	Ref<mgl::Scene> scene = CreateRef<MyScene>(window);
	window->addScene("main", scene);
	window->setScene("main");

	app->addWindow(window);
	app->run();
	return 0;
}