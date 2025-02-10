#include <graphics/render/pointshadow.hpp>
#include <graphics/render/pointlight.hpp>
#include <math/projection.hpp>
#include <cassert>
#include <glad/gl.h>

namespace mgl
{
	static Ref<ShaderProgram> shader;

	PointShadow::PointShadow(RenderContext* context, float bias, int sampleRadius) :
		Shadow(context, bias, sampleRadius) {}

	void PointShadow::create(const mml::uvec2& size)
	{
		this->size = size;
		this->bias = bias;
		this->sampleRadius = sampleRadius;

		camera = CreateRef<PerspectiveCamera>();
		camera->perspective((float)mml::PI / 2.0f, 0.1f, 10.0f, (float)size.x / size.y);

		cubemap = context->createCubeMap();
		cubemap->allocate(size.x, size.y, TextureFormat::DEPTH);

		framebuffer = context->createFrameBuffer();
		framebuffer->bind();
		//framebuffer->addRenderTarget(cubemap, FrameBufferAttachment{FrameBufferAttachmentType::DEPTH});
		framebuffer->setShaderColorOutputLoc();
		framebuffer->unbind();
		
		static bool init = false;

		if(!init) {
			shader = context->createShaderProgram();
			shader->attachGLSLShadersFromSrc(
			R"(#version 430 core
			layout (location = 0) in vec3 v_pos;

			uniform mat4 u_transform;

			void main()
			{
				gl_Position = vec4(v_pos, 1.0) * u_transform;
			})",

			R"(#version 430 core

			in vec4 fragPos;
			uniform float u_farPlane;
			uniform vec3 u_lightPos;

			void main()
			{
				gl_FragDepth = length(fragPos.xyz - u_lightPos) / u_farPlane;
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

			init = true;
		}
	}

	Ref<ShaderProgram> PointShadow::getShader() const
	{
		return shader;
	}

	Ref<Camera> PointShadow::getCamera() const
	{
		return camera;
	}
}