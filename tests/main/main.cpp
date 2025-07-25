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
#include <graphics/geometry/shape3d.hpp>
#include <graphics/render/renderer.hpp>
#include <graphics/camera/firstperson.hpp>
#include <math/random.hpp>

#include <graphics/render/directionallight.hpp>
#include <graphics/render/pointlight.hpp>
#include <graphics/render/renderscene.hpp>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_mgl.h>
#include <imgui/imgui_impl_win32.h>

#include <resourceloader/modelloader.hpp>
#include <graphics/geometry/util.hpp>
#include <graphics/render/shadervariant.hpp>

class MyScene : public mgl::Scene
{
public:
	Ref<mgl::Window> window;
	Ref<mgl::Renderer> renderer;
	Ref<mgl::RenderContext> context;
	Ref<mgl::FirstPersonCamera> camera;
	Ref<mgl::DirectionalLight> light;
	//Ref<mgl::PointLight> light;

	Ref<mgl::RenderScene> renderScene;
	float i = 0.0f;

	Ref<mgl::Model> lightCube;
	
	MyScene(const Ref<mgl::Window>& window) :
		window(window)
	{
		context = window->getContext();
		context->setDepthTest(true);

		renderer = CreateRef<mgl::Renderer>(context.get(), window->getSize());
		Ref<mgl::DeferredGeometryPass> geometryPass = CreateRef<mgl::DeferredGeometryPass>(context.get(), window->getSize());
		renderer->geometryPasses.push_back(geometryPass);
		renderer->lightingPasses.push_back(CreateRef<mgl::DeferredLightingPass>(context.get(), geometryPass));
		//renderer->geometryPasses.push_back(CreateRef<mgl::ShadowGeometryPass>());
		//renderer->lightingPasses.push_back(CreateRef<mgl::ForwardLightingPass>());
		//renderer->filters.push_back(CreateRef<mgl::EdgeFilter>(context.get(), window->getSize()));
		//renderer->filters.push_back(CreateRef<mgl::BlurFilter>(context.get(), window->getSize()));

		renderScene = CreateRef<mgl::RenderScene>();

		//{
		//	Ref<mgl::Texture2D> texture = context->createTexture2D();
		//	texture->loadFromFile(R"(C:\Users\tony3\Downloads\iiii.png)");

		//	Ref<mgl::StandardMaterial> material = CreateRef<mgl::StandardMaterial>(context.get());
		//	material->diffuseMap = texture;

		//	Ref<mgl::Mesh> mesh = context->createMesh();
		//	mesh->setGeometry(mgl::gl::Shape3D().SphereUVN(20, 20));

		//	Ref<mgl::Model> sphere;
		//	sphere = CreateRef<mgl::Model>();
		//	sphere->setMesh(mesh);
		//	sphere->setMaterial(material);
		//	renderScene->addModel(sphere);
		//}

		{
			//Ref<mgl::StandardMaterial> material = CreateRef<mgl::StandardMaterial>(context.get(), mgl::StandardShaderVairant(mgl::RenderPipeline::FORWARD, false, false, false, 0, 1));
			Ref<mgl::StandardMaterial> material = CreateRef<mgl::StandardMaterial>(context.get(), mgl::StandardShaderVairant(mgl::RenderPipeline::DEFERRED, false, false, false, 1, 0));
			material->albedo = mml::color(1, 1, 0, 1);

			mrl::ModelLoader loader;
			mrl::ObjModelData data = loader.loadObj("tests/main/human.obj");

			for(mrl::ObjMeshData& meshData : data.meshes) {

				Ref<mgl::Model> model = CreateRef<mgl::Model>();
				Ref<mgl::Mesh> mesh = context->createMesh();

				mgl::Geometry<mgl::gl::Vertex3DUVN, GLuint> geometry = {
					meshData.vertices,
					meshData.indices
				};

				std::cout << meshData.vertices.size() << ", " << meshData.indices.size() << '\n';

				mgl::calculateFlatNormals(geometry);
				mesh->setGeometry(geometry);

				model->setMesh(mesh);
				model->setPos(mml::vec3(0));
				model->setScale(mml::vec3(0.1f));
				
				model->setMaterial(material);
				renderScene->addModel(model);
			}
		}

		{
			Ref<mgl::Texture2D> texture = context->createTexture2D();
			texture->loadFromFile(R"(C:\Users\tony3\Downloads\rickandmorty.jpg)");

			//Ref<mgl::StandardMaterial> material = CreateRef<mgl::StandardMaterial>(context.get(), mgl::StandardShaderVairant(mgl::RenderPipeline::FORWARD, true, false, false, 0, 1));
			Ref<mgl::StandardMaterial> material = CreateRef<mgl::StandardMaterial>(context.get(), mgl::StandardShaderVairant(mgl::RenderPipeline::DEFERRED, true, false, false, 1, 0));
			material->diffuseMap = texture;

			Ref<mgl::Mesh> mesh = context->createMesh();
			mesh->setGeometry(mgl::gl::Shape3D().CubeUVN());

			Ref<mgl::Model> ground = CreateRef<mgl::Model>();
			ground->setPos(mml::vec3(0));
			ground->setScale(mml::vec3(2, 0.1f, 2));

			ground->setMesh(mesh);
			ground->setMaterial(material);
			renderScene->addModel(ground);
		}

		//{
		//	Ref<mgl::BasicMaterial> material = CreateRef<mgl::BasicMaterial>(context.get());
		//	material->color = mml::color(1);

		//	Ref<mgl::Mesh> mesh = context->createMesh();
		//	mesh->setGeometry(mgl::gl::Shape3D().Cube());

		//	lightCube = CreateRef<mgl::Model>();
		//	lightCube->setScale(mml::vec3(0.1f));
		//	lightCube->setMesh(mesh);
		//	lightCube->setMaterial(material);
		//	renderScene->addModel(lightCube);
		//}

		//light = CreateRef<mgl::PointLight>(mml::vec3(-0.2f, -1.0f, -0.3f), mml::color(1), 0.3f);
		//light->createShadow(context.get(), mml::uvec2(window->getWidth(), window->getWidth()));

		light = CreateRef<mgl::DirectionalLight>(mml::vec3(-0.2f, -1.0f, -0.3f), mml::color(1), 0.3f);
		light->createShadow(context.get(), mml::uvec2(window->getWidth(), window->getHeight()));
		renderScene->addLight(light);


		//light2 = CreateRef<mgl::DirectionalLight>(mml::vec3(-0.2f, -1.0f, -0.3f), mml::color(1), 0.3f);
		//light2->createShadow(context.get(), mml::uvec2(window->getWidth()));
		//renderScene->addLight(light2);

		camera = CreateRef<mgl::FirstPersonCamera>();
		renderScene->setCamera(camera);
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
		context->viewport(0, 0, window->getWidth(), window->getHeight());

		window->setTitle(mil::getMousePos().toString());

		if(mil::isKeyPressed(mil::Key::K_0)) {
			std::cout << "Asd";  
		}

		i += 0.001f;

		//material->color = mml::color(mml::sin(i) * 0.5f + 1, mml::cos(i) * 0.5f + 1, 0, 1);
		//model->setScale(mml::vec3(model->getScale().x + mml::cos(i * 10.0f) / 1000));

		//renderScene->getModels()[0]->setRotate(mml::vec3(i, 0, 0));

		//lightCube->setPos(light->pos);

		camera->BasicFirstPersonView(window);
		camera->calculate();
		camera->perspective(45.0f, 0.1f, 1000.0f, window->getSize());
		
		renderer->render(renderScene);
		imguiRender();
	}

	void lowLevelMsgLoopCallback(void* hWnd, unsigned int uMsg, unsigned int wParam, long lParam)
	{
		static bool initImGui = false;
		if(!initImGui) {
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			ImGui::StyleColorsDark();

			ImGui_ImplWin32_InitForOpenGL(hWnd);
			ImGui_ImplOpenGL3_Init();
			initImGui = true;
		}

		if(ImGui_ImplMgl_WndProcHandler(hWnd, uMsg, wParam, lParam))
			window->preventDefaultCallback();
	}

	void imguiRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Light");
		//ImGui::DragFloat3("lightPos", &light->pos, 0.1f);
		ImGui::DragFloat3("lightDir", &light->dir, 0.1f);
		ImGui::Image((ImTextureID)4, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		//ImGui::Begin("Light2");
		//ImGui::DragFloat3("lightPos", &light2->dir, 0.1f);
		//ImGui::Image((ImTextureID)4, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		//ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};


//class MyScene : public mgl::Scene
//{
//public:
//	Ref<mgl::Window> window;
//	Ref<mgl::Renderer> renderer;
//	Ref<mgl::RenderContext> context;
//	
//	Ref<mgl::FirstPersonCamera> camera;
//	Ref<mgl::Mesh> mesh;
//	
//	Ref<mgl::BasicMaterial> material;
//
//	MyScene(const Ref<mgl::Window>& window) :
//		window(window)
//	{
//		context = window->getContext();
//		renderer = mgl::createRenderer();
//
//		material = CreateRef<mgl::BasicMaterial>(context.get());
//		material->color = mml::color(1, 0, 0, 1);
//
//		mesh = context->createMesh();
//		mesh->create();
//		mesh->setGeometry(mgl::gl::Shape3D(mml::vec3(0), mml::vec3(0.5f)).Cube());
//	
//		camera = CreateRef<mgl::FirstPersonCamera>();
//		camera->speed = 0.01f;
//	}
//
//	void update()
//	{
//		context->clearColor();
//		context->clearDepth();
//
//		camera->BasicFirstPersonView(window);
//		camera->perspective(45.0f, 0.1f, 1000.0f, window->getSize());
//
//		material->shader->bind();
//		material->use();
//		material->shader->uniform("u_projection", camera->projView);
//		material->shader->uniform("u_transform", mml::mat4(1));
//		
//		mesh->draw(material->shader);
//	}
//};

int main()
{
	Ref<mgl::App> app = CreateRef<mgl::App>(mgl::RenderApi::OPENGL);
	Ref<mgl::Window> window = CreateRef<mgl::Window>("hello world", 1200, 700);
	
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