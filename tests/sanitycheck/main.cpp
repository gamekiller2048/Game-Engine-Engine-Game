#include <input/input.hpp>
#include <graphics/window.hpp>
#include <graphics/app.hpp>
#include <graphics/render/opengl/glcontext.hpp>
#include <graphics/render/mesh.hpp>
#include <graphics/geometry/shape2d.hpp>

class MyScene : public mgl::Scene
{
public:
    Ref<mgl::Window> window;
    Ref<mgl::RenderContext> context;
    
    Ref<mgl::Mesh> screenQuad;
    Ref<mgl::ShaderProgram> shader;
    
    Ref<mgl::Texture2D> textureA;
    Ref<mgl::Texture2D> textureB;

    
    MyScene(const Ref<mgl::Window>& window) :
        window(window)
    {
        context = window->getContext();
        context->setDepthTest(true);


        screenQuad = context->createMesh();
        screenQuad->setGeometry(mgl::gl::Shape2D().SquareUV());

        shader = context->createShaderProgram();
        shader->attachGLSLShadersFromFile("tests/sanitycheck/shader.vert", "tests/sanitycheck/shader.frag");
        

        textureA = context->createTexture2D();
        textureA->loadFromFile(R"(C:\Users\tony3\Downloads\2025-05-20T22.18.47_1.jpg)");

        textureB = context->createTexture2D();
        textureB->loadFromFile(R"(C:\Users\tony3\Downloads\Shinobu_anime_design.png)");
        
        shader->bind();
        textureA->uniformSampler(shader, "u_tex");
    }

    void update()
    {
        context->clearColor();
        context->clearDepth();
        context->viewport(0, 0, window->getWidth(), window->getHeight());

        textureA->bindUnit();
        shader->bind();
        screenQuad->draw(shader);

    }
};

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