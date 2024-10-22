#include <graphics/render/pointshadow.hpp>
#include <graphics/render/pointlight.hpp>
#include <math/projection.hpp>
#include <cassert>

namespace mgl
{
	PointShadow::PointShadow(float bias, int sampleRadius) :
		Shadow(bias, sampleRadius) {}

	void PointShadow::create(const mml::uvec2& size, uint texUnit)
	{
		this->size = size;
		this->bias = bias;
		this->sampleRadius = sampleRadius;

		cubemap.create();
		cubemap.allocate(size.x, size.y, Format::DEPTH, Format::DEPTH, Primative::UBYTE, texUnit, {}, true);

		fbo.create();
		fbo.attachTexture(cubemap, Attachment::DEPTH);
		fbo.setDrawAttachments({ GL_NONE });
		fbo.setReadAttachment({ GL_NONE });
		fbo.unbind();

		shader.create();
		shader.attachShaders(
			R"(#version 430 core
			layout (location = 0) in vec3 v_pos;

			uniform mat4 u_model;

			void main()
			{
				gl_Position = vec4(v_pos, 1.0) * u_model;
			})",

			R"(#version 430 core

			in vec4 fragPos;
			uniform float u_farPlane;
			uniform vec3 u_lightPos;

			void main()
			{
				gl_FragDepth = length(fragPos.xyz - u_lightPos) / 50.0f;
			})",

			R"(#version 430 core
			layout (triangles) in;
			layout (triangle_strip, max_vertices=18) out;

			uniform mat4 u_shadowMats[6];
			out vec4 fragPos;

			void main()
			{
				for(int face=0; face < 6; face++) {
					gl_Layer = face;
					for(int i=0; i < 3; i++) {
						fragPos = gl_in[i].gl_Position;
						gl_Position = fragPos * u_shadowMats[face];
						EmitVertex();
					}
					EndPrimitive();
				}
			})"
		);
	}

	void PointShadow::startFrame() const
	{
		fbo.bind();
		fbo.viewport(0, 0, size.x, size.y);
		fbo.clear(BufferBit::DEPTH);
	}

	void PointShadow::endFrame() const
	{
		fbo.unbind();
	}

	void PointShadow::use(const Ref<Light>& light)
	{
		const Ref<PointLight>& pointLight = std::static_pointer_cast<PointLight>(light);

		mml::mat4 shadowProj = mml::perspective((float)mml::PI / 2.0f, 10.0f, 0.1f, (float)size.x / size.y);
		std::vector<mml::mat4> shadowTransforms = {
			shadowProj * mml::lookAt(pointLight->pos, pointLight->pos + mml::RIGHT, mml::DOWN),
			shadowProj * mml::lookAt(pointLight->pos, pointLight->pos + mml::LEFT, mml::DOWN),
			shadowProj * mml::lookAt(pointLight->pos, pointLight->pos + mml::UP, mml::FORWARD),
			shadowProj * mml::lookAt(pointLight->pos, pointLight->pos + mml::DOWN, mml::BACKWARD),
			shadowProj * mml::lookAt(pointLight->pos, pointLight->pos + mml::FORWARD, mml::DOWN),
			shadowProj * mml::lookAt(pointLight->pos, pointLight->pos + mml::BACKWARD, mml::DOWN)
		};

		shader.uniformMat4s("u_shadowMats", shadowTransforms);
		shader.uniformVec3("u_lightPos", pointLight->pos);
		shader.uniformFloat("u_farPlane", 1);
	}
}