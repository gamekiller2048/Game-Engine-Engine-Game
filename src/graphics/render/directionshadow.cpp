#include <graphics/render/directionalshadow.hpp>
#include <graphics/render/directionallight.hpp>
#include <math/projection.hpp>
#include <cassert>

namespace mgl
{
    static Ref<ShaderProgram> shader;

    DirectionalShadow::DirectionalShadow(RenderContext* context, float bias, int sampleRadius) :
        Shadow(context, bias, sampleRadius) {}

    void DirectionalShadow::create(const mml::uvec2& size)
    {
        this->size = size;
        this->bias = bias;
        this->sampleRadius = sampleRadius;

        camera = CreateRef<OrthographicCamera>();
        camera->orthographic(5.0f, -5.0f, 5.0f, -5.0f, -5.0f, 5.0f);

        framebuffer = context->createFrameBuffer();
        framebuffer->bind();

        map = context->createTexture2D();
        map->allocate(size.x, size.y, mgl::TextureFormat::DEPTH, mgl::TextureFormat::RGBA32F);
        
        map->bindUnit();
        framebuffer->addRenderTarget(map, FrameBufferAttachment{FrameBufferAttachmentType::DEPTH});
        framebuffer->setShaderColorOutputLoc();
        framebuffer->unbind();

        static bool init = false;

        if(!init) {
            shader = context->createShaderProgram();
            shader->attachGLSLShadersFromSrc(
                R"(#version 430 core
                layout (location = 0) in vec3 v_pos;

                uniform mat4 u_lightSpaceTransform;
                uniform mat4 u_transform;

                void main()
                {
                    gl_Position = vec4(v_pos, 1.0) * u_transform * u_lightSpaceTransform;
                })",

                R"(#version 430 core

                void main()
                {
                })"
            );

            init = true;
        }
    }

    Ref<Texture2D> DirectionalShadow::getMap() const
    {
        return map;
    }

    Ref<ShaderProgram> DirectionalShadow::getShader() const
    {
        return shader;
    }

    Ref<Camera> DirectionalShadow::getCamera() const
    {
        return camera;
    }
}