#include <graphics/render/filter.hpp>
#include <graphics/geometry/shape2d.hpp>
#include <algorithm>
#include <vector>

#include <graphics/render/opengl/gltexture2d.hpp>
#include "opengl/gltexture2dimpl.hpp"

namespace mgl
{
	Filter::Filter(RenderContext* context, const mml::uvec2 size)
	{
		shader = context->createShaderProgram();
		framebuffer = context->createFrameBuffer();
		framebuffer->bind();

		output = context->createTexture2D();
		output->allocate(size.x, size.y, TextureFormat::RGBA);
		output->bind();
		framebuffer->addRenderTarget(output, FrameBufferAttachment{FrameBufferAttachmentType::COLOR});
		framebuffer->unbind();

		quad = context->createMesh();
		quad->setGeometry(gl::Shape2D().SquareUV());
	}

	Ref<Texture2D> Filter::apply(const Ref<Texture2D>& input) const
	{
		framebuffer->bind();
		shader->bind();
		input->bindUnit();
		input->uniformSampler(shader, "u_screen");
		quad->draw(shader);
		framebuffer->unbind();
		return output;
	}

	ConvolutionFilter::ConvolutionFilter(RenderContext* context, const std::array<float, 9>& kernel, const mml::uvec2 size) :
		Filter(context, size), kernel(kernel)
	{
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

			uniform sampler2D u_screen;

			const float offset = 1.0 / 300.0;

			uniform float u_kernel[9];

			void main()
			{
				vec2 offsets[9] = vec2[](
					vec2(-offset,  offset), // top-left
					vec2( 0.0f,    offset), // top-center
					vec2( offset,  offset), // top-right
					vec2(-offset,  0.0f),   // center-left
					vec2( 0.0f,    0.0f),   // center-center
					vec2( offset,  0.0f),   // center-right
					vec2(-offset, -offset), // bottom-left
					vec2( 0.0f,   -offset), // bottom-center
					vec2( offset, -offset)  // bottom-right    
				);

				vec3 sampleTex[9];
				for(int i = 0; i < 9; i++)
					sampleTex[i] = vec3(texture(u_screen, texUV.xy + offsets[i]));

				vec3 col = vec3(0.0);
				for(int i = 0; i < 9; i++)
					col += sampleTex[i] * u_kernel[i];

				gl_FragColor = vec4(col, 1.0f);
			})"
		);

		shader->bind();
		shader->uniforms("u_kernel", std::vector<float>(kernel.begin(), kernel.end()));
	}

	BlurFilter::BlurFilter(RenderContext* context, const mml::uvec2 size) :
		ConvolutionFilter(context,
			{1.0f / 16, 2.0f / 16, 1.0f / 16,
			2.0f / 16, 4.0f / 16, 2.0f / 16,
			1.0f / 16, 2.0f / 16, 1.0f / 16}, size) {}

	SharpenFilter::SharpenFilter(RenderContext* context, const mml::uvec2 size) :
		ConvolutionFilter(context,
			{-1.0f, -1.0f, -1.0f,
			-1.0f, 9.0f, -1.0f,
			-1.0f, -1.0f, -1.0f }, size) {}

	EdgeFilter::EdgeFilter(RenderContext* context, const mml::uvec2 size) :
		ConvolutionFilter(context,
			{1.0f, 1.0f, 1.0f,
			1.0f, -8.0f, 1.0f,
			1.0f, 1.0f, 1.0f}, size) {}
}