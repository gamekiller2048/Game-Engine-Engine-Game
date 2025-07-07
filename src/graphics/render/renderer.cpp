#include <graphics/render/renderer.hpp>
#include <graphics/app.hpp>
#include <graphics/geometry/shape2d.hpp>

#include <graphics/render/opengl/gltexture2d.hpp>
#include "opengl/gltexture2dimpl.hpp"

namespace mgl
{
    void ForwardLightingPass::render(const Ref<RenderScene>& scene) const
    {
        for(const Ref<Model>& model : scene->getModels()) {
            Ref<mgl::ShaderProgram> shader = model->getMaterial()->shader;
            shader->bind();
            shader->uniform("u_projection", scene->getCamera()->projView);
            shader->uniform("u_transform", model->getTransform());

            for(uint i = 0; i < scene->getLights().size(); i++)
                scene->getLights()[i]->use(shader, i);

            model->getMaterial()->use();
            model->getMesh()->draw(shader);
        }
    }


    void ShadowGeometryPass::render(const Ref<RenderScene>& scene) const
    {
        for(const Ref<Light>& light : scene->getLights()) {
            if(light->getShadow()) {
                Ref<Shadow> shadow = light->getShadow();
                Ref<mgl::ShaderProgram> shader = shadow->getShader();

                shader->bind();
                light->useShadow();
                shadow->startFrame();

                for(const Ref<Model>& model : scene->getModels()) {
                    shader->uniform("u_transform", model->getTransform());
                    model->getMesh()->draw(shader);
                }

                shadow->endFrame();
            }
        }
    }

    DeferredGeometryPass::DeferredGeometryPass(RenderContext* context, const mml::uvec2& size)
    {
        framebuffer = context->createFrameBuffer();
        framebuffer->bind();

        // depth attachment required for depth testing
        // TODO: use renderbuffer
        depthOutput = context->createTexture2D();
        depthOutput->allocate(size.x, size.y, mgl::TextureFormat::DEPTH, TextureFormat::DEPTH);
        framebuffer->addRenderTarget(depthOutput, FrameBufferAttachment{FrameBufferAttachmentType::DEPTH});
        framebuffer->unbind();

        position = context->createTexture2D();
        position->allocate(size.x, size.y, TextureFormat::RGB, TextureFormat::RGB);
        
        position->bindUnit();
        framebuffer->addRenderTarget(position, FrameBufferAttachment{FrameBufferAttachmentType::COLOR, 0}, 0);

        normal = context->createTexture2D();
        normal->allocate(size.x, size.y, TextureFormat::RGB, TextureFormat::RGB);
        
        normal->bindUnit();
        framebuffer->addRenderTarget(normal, FrameBufferAttachment{FrameBufferAttachmentType::COLOR, 1}, 1);

        albeodoSpecular = context->createTexture2D();
        albeodoSpecular->allocate(size.x, size.y, TextureFormat::RGBA, TextureFormat::RGBA);

        albeodoSpecular->bindUnit();
        framebuffer->addRenderTarget(albeodoSpecular, FrameBufferAttachment{FrameBufferAttachmentType::COLOR, 2}, 2);


        framebuffer->setShaderColorOutputLoc();
        framebuffer->unbind();
    }

    void DeferredGeometryPass::render(const Ref<RenderScene>& scene) const
    {
        framebuffer->bind();
        framebuffer->clear(mgl::FrameBufferAttachmentType::COLOR);
        framebuffer->clear(mgl::FrameBufferAttachmentType::DEPTH);

        for(const Ref<Model>& model : scene->getModels()) {
            Ref<mgl::ShaderProgram> shader = model->getMaterial()->shader;
            shader->bind();
            shader->uniform("u_projection", scene->getCamera()->projView);
            shader->uniform("u_transform", model->getTransform());
            model->getMesh()->draw(shader);
        }
        framebuffer->unbind();
    }

    DeferredLightingPass::DeferredLightingPass(RenderContext* context, const Ref<DeferredGeometryPass>& geometryPass) :
        geometryPass(geometryPass)
    {
        shader = context->createShaderProgram();
        shader->attachGLSLShadersFromSrc(
            R"(
            #version 430 core
            layout(location = 0) in vec2 v_pos;
            layout(location = 1) in vec2 v_texUV;

            out vec2 texUV;
                
            void main()
            {
                texUV = v_texUV;
                gl_Position = vec4(v_pos, 0.0f, 1.0f);
            })",

            R"(
            #version 430 core
            in vec2 texUV;

            uniform sampler2D gPosition;
            uniform sampler2D gNormal;
            uniform sampler2D gAlbedoSpec;

            void main()
            {
                vec3 pos = texture(gPosition, texUV).rgb;
                vec3 normal = texture(gNormal, texUV).rgb;
                vec3 albedo = texture(gAlbedoSpec, texUV).rgb;
                float specular = texture(gAlbedoSpec, texUV).a;

                vec3 lightPos = vec3(1);
                vec3 lightDir = normalize(lightPos - pos);
                float diffuse = max(dot(normal, lightDir), 0.0);
    
                gl_FragColor = vec4(vec3(1) * diffuse, 1.0);
            })"
        );

        quad = context->createMesh();
        quad->setGeometry(gl::Shape2D().SquareUV());
    }

    void DeferredLightingPass::render(const Ref<RenderScene>& scene) const
    {
        shader->bind();

        geometryPass->position->bindUnit();
        geometryPass->position->uniformSampler(shader, "gPosition");

        geometryPass->normal->bindUnit();
        geometryPass->normal->uniformSampler(shader, "gNormal");
        
        geometryPass->albeodoSpecular->bindUnit();
        geometryPass->albeodoSpecular->uniformSampler(shader, "gAlbedoSpec");

        quad->draw(shader);
    }

    Renderer::Renderer(RenderContext* context, const mml::uvec2& size)
    {
        framebuffer = context->createFrameBuffer();
        
        renderOutput = context->createTexture2D();
        renderOutput->allocate(size.x, size.y, mgl::TextureFormat::RGBA, mgl::TextureFormat::RGBA);
       
        renderOutput->bindUnit();
        framebuffer->addRenderTarget(renderOutput, FrameBufferAttachment{FrameBufferAttachmentType::COLOR});
        
        //depth attachment required for depth testing
        // TODO: use renderbuffer
        depthOutput = context->createTexture2D();
        depthOutput->allocate(size.x, size.y, mgl::TextureFormat::DEPTH, TextureFormat::DEPTH);
        
        depthOutput->bindUnit();
        framebuffer->addRenderTarget(depthOutput, FrameBufferAttachment{FrameBufferAttachmentType::DEPTH});
        framebuffer->unbind();

        shader = context->createShaderProgram();
        shader->attachGLSLShadersFromSrc(
            R"(
            #version 430 core
            layout(location = 0) in vec2 v_pos;
            layout(location = 1) in vec2 v_texUV;

            out vec2 texUV;

            void main()
            {
                gl_Position = vec4(v_pos, 0.0f, 1.0f);
                texUV = v_texUV;
            })",

            R"(
            #version 430 core
            
            in vec2 texUV;
            in vec3 pos;

            uniform sampler2D u_screen;

            void main()
            {    
                gl_FragColor = texture(u_screen, texUV);
            })"
        );

        quad = context->createMesh();
        quad->setGeometry(gl::Shape2D().SquareUV());
    }

    void Renderer::render(const Ref<RenderScene>& scene) const
    {
        for(const Ref<GeometryPass>& pass : geometryPasses)
            pass->render(scene);

        framebuffer->bind();
        framebuffer->clear(FrameBufferAttachmentType::COLOR);
        framebuffer->clear(FrameBufferAttachmentType::DEPTH);
        for(const Ref<LightingPass>& pass : lightingPasses)
            pass->render(scene);
        framebuffer->unbind();

        Ref<Texture2D> input = renderOutput;
        for(const Ref<Filter>& filter : filters)
            input = filter->apply(input);
        
        shader->bind();
        input->bindUnit();
        input->uniformSampler(shader, "u_screen");
        quad->draw(shader);
    }
}