#include <graphics/render/directionalshadow.hpp>
#include <graphics/render/directionallight.hpp>
#include <math/projection.hpp>
#include <cassert>

namespace mgl
{
	DirectionalShadow::DirectionalShadow(float bias, int sampleRadius) :
		Shadow(bias, sampleRadius) {}

	void DirectionalShadow::create(const mml::uvec2& size, uint texUnit)
	{
		this->size = size;
		this->bias = bias;
		this->sampleRadius = sampleRadius;

		map.create();
		map.allocate(size.x, size.y, Format::DEPTH, Format::DEPTH, Primative::UBYTE, texUnit, {}, true);

		fbo.create();
		fbo.attachTexture(map, Attachment::DEPTH);
		fbo.setDrawAttachments({ GL_NONE });
		fbo.setReadAttachment({ GL_NONE });
		fbo.unbind();

		shader.create();
		shader.attachShaders(
			R"(#version 430 core
			layout (location = 0) in vec3 v_pos;

			uniform mat4 u_lightSpaceTransform;
			uniform mat4 u_model;

			void main()
			{
				gl_Position = vec4(v_pos, 1.0) * u_model * u_lightSpaceTransform;
			})",

			R"(#version 430 core

			void main()
			{
			})"
		);
	}

	void DirectionalShadow::startFrame() const
	{
		fbo.bind();
		fbo.viewport(0, 0, size.x, size.y);
		fbo.clear(BufferBit::DEPTH);
	}

	void DirectionalShadow::endFrame() const
	{
		fbo.unbind();
	}

	void DirectionalShadow::use(const Ref<Light>& light)
	{
		const Ref<DirectionalLight>& directionalLight = std::static_pointer_cast<DirectionalLight>(light);
		shader.uniformMat4("u_lightSpaceTransform", directionalLight->getSpaceTransform());
	}
}