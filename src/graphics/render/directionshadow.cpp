#include <graphics/render/directionalshadow.hpp>
#include <graphics/render/directionallight.hpp>
#include <math/projection.hpp>
#include <cassert>

namespace mgl
{
	static Ref<ShaderProgram> shader;

	DirectionalShadow::DirectionalShadow(float bias, int sampleRadius) :
		Shadow(bias, sampleRadius) {}

	void DirectionalShadow::create(const mml::uvec2& size)
	{
		this->size = size;
		this->bias = bias;
		this->sampleRadius = sampleRadius;

		camera = CreateRef<OrthographicCamera>();
		camera->orthographic(10.0f, -10.0f, 10.0f, -10.0f, 500.0f, 0.1f);

		map = CreateRef<gl::Texture2D>();
		map->create();
		map->allocate(size.x, size.y, gl::Format::DEPTH, gl::Format::DEPTH, gl::Primative::UBYTE, {}, true);

		fbo.create();
		fbo.attachTexture(*map.get(), gl::Attachment::DEPTH);
		fbo.setDrawAttachments({GL_NONE});
		fbo.setReadAttachment({GL_NONE});
		fbo.unbind();

		static bool init = false;

		if(!init) {
			shader = createShaderProgram();
			shader->create();
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

	Ref<gl::Texture2D> DirectionalShadow::getMap() const
	{
		return map;
	}
	Ref<ShaderProgram> DirectionalShadow::getShader() const
	{
		return shader;
	}
}