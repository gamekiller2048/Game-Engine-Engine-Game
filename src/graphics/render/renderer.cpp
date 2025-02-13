#include <graphics/render/renderer.hpp>
#include <graphics/app.hpp>
#include <graphics/geometry/shape2d.hpp>

namespace mgl
{
	void ForwardRenderPass::render(const Ref<RenderScene>& scene) const
	{
		for(const Ref<Model>& model : scene->getModels()) {
			Ref<mgl::ShaderProgram> shader = model->getMaterial()->shader;
			shader->bind();
			shader->uniform("u_projection", scene->getCamera()->projView);
			shader->uniform("u_transform", model->getTransform());

			for(int i = 0; i < scene->getLights().size(); i++)
				scene->getLights()[i]->use(shader, i);

			model->getMaterial()->use();
			model->getMesh()->draw(shader);
		}
	}

	void ShadowRenderPass::render(const Ref<RenderScene>& scene) const
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

	DeferredGeometryRenderPass::DeferredGeometryRenderPass(RenderContext* context, const mml::uvec2& size)
	{
		shader = context->createShaderProgram();
		shader->attachGLSLShadersFromSrc(
			R"(
			#version 430 core
			layout(location = 0) in vec3 v_pos;
			layout(location = 1) in vec2 v_texUV;
			layout(location = 2) in vec3 v_normal;

			uniform mat4 u_projection;
			uniform mat4 u_transform;

			out vec2 texUV;
			out vec3 pos;
			out vec3 normal;

			void main()
			{
				vec4 p = vec4(v_pos, 1) * u_transform;
				pos = vec3(p);
				normal = normalize(v_normal);
				gl_Position = p * u_projection;

				texUV = v_texUV;
			}
			)",

			R"(
			#version 430 core
			layout (location = 0) out vec3 gPosition;
			layout (location = 1) out vec3 gNormal;
			layout (location = 2) out vec4 gAlbedoSpec;

			in vec2 texUV;
			in vec3 pos;
			in vec3 normal;

			uniform sampler2D diffuse;
			uniform sampler2D specular;

			void main()
			{    
				gPosition = pos;
				gNormal = normal;
				gAlbedoSpec.rgb = texture(diffuse, texUV).rgb;
				gAlbedoSpec.a = texture(specular, texUV).r;
			}  
			)"
		);

		framebuffer = context->createFrameBuffer();
		framebuffer->bind();

		position = context->createTexture2D();
		position->allocate(size.x, size.y, TextureFormat::RGB);
		position->bind();
		framebuffer->addRenderTarget(position, FrameBufferAttachment{FrameBufferAttachmentType::COLOR, 0}, 0);

		normal = context->createTexture2D();
		normal->allocate(size.x, size.y, TextureFormat::RGB);
		normal->bind();
		framebuffer->addRenderTarget(normal, FrameBufferAttachment{FrameBufferAttachmentType::COLOR, 1}, 1);

		albeodoSpecular = context->createTexture2D();
		albeodoSpecular->allocate(size.x, size.y, TextureFormat::RGBA);
		albeodoSpecular->bind();
		framebuffer->addRenderTarget(albeodoSpecular, FrameBufferAttachment{FrameBufferAttachmentType::COLOR, 2}, 2);


		framebuffer->setShaderColorOutputLoc();
		framebuffer->unbind();
	}

	void DeferredGeometryRenderPass::render(const Ref<RenderScene>& scene) const
	{
		framebuffer->bind();
		framebuffer->clear(mgl::FrameBufferAttachmentType::COLOR);
		framebuffer->clear(mgl::FrameBufferAttachmentType::DEPTH);

		for(const Ref<Model>& model : scene->getModels()) {
			shader->bind();
			shader->uniform("u_projection", scene->getCamera()->projView);
			shader->uniform("u_transform", model->getTransform());
			model->getMesh()->draw(shader);
		}
		framebuffer->unbind();
	}

	DeferredLightingRenderPass::DeferredLightingRenderPass(RenderContext* context)
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
			}
			)",

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
	
				gl_FragColor = vec4(clamp(normal.xyz, 0, 1), 1.0);
			}
			)"
		);

		quad = context->createMesh();
		quad->setGeometry(gl::Shape2D().SquareUV());
	}

	void DeferredLightingRenderPass::render(const Ref<RenderScene>& scene) const
	{
		quad->draw(shader);
	}

	DeferredRenderPass::DeferredRenderPass(RenderContext* context, const mml::uvec2& size) :
		geometryPass(context, size), lightingPass(context) {}

	void DeferredRenderPass::render(const Ref<RenderScene>& scene) const
	{
		geometryPass.render(scene);

		lightingPass.shader->bind();

		geometryPass.position->bind();
		geometryPass.normal->bind();
		geometryPass.albeodoSpecular->bind();

		geometryPass.position->uniformSampler(lightingPass.shader, "gPosition");
		geometryPass.normal->uniformSampler(lightingPass.shader, "gNormal");
		geometryPass.albeodoSpecular->uniformSampler(lightingPass.shader, "gAlbedoSpec");
		lightingPass.render(scene);
	}

	void Renderer::render(const Ref<RenderScene>& scene) const
	{
		for(const Ref<RenderPass>& renderPass : renderPasses)
			renderPass->render(scene);
	}
}