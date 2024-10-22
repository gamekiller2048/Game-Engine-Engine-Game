#include <graphics/render/postprocess.hpp>

namespace mgl
{
	void PostProcess::createKernelShader()
	{
		kernelShader.create();
		kernelShader.attachShaders(
			R"(#version 430 core
			layout (location = 0) in vec2 v_pos;
			layout (location = 1) in vec2 v_texUV;

			out vec2 texUV;

			void main()
			{
				texUV = v_texUV;
				gl_Position = vec4(v_pos, 0, 1); 
			})",

			R"(#version 430 core
			in vec2 texUV;

			const float offset = 1 / 300.0f;

			const vec2 offsets[9] = vec2[](
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

			uniform mat3 kernel;
			uniform sampler2D tex;

			void main()
			{
				vec3 sampleTex[9];
				for(int i=0; i < 9; i++)
					sampleTex[i] = vec3(texture(tex, texUV.xy + offsets[i]));

				vec3 col = vec3(0);
				for(int i=0; i < 9; i++)
					col += sampleTex[i] * kernel[i % 3][i / 3];
    
				gl_FragColor = vec4(col, 1);
			})");
	}

	void PostProcess::create(const mml::uvec2& size)
	{
		texture.create();
		texture.allocate(size.x, size.y, Format::RGB, Format::RGB, Primative::UBYTE, 0, TexFilterOptions {TexFilter::NEAREST, TexFilter::NEAREST, TexFilter::CLAMP_EDGE, TexFilter::CLAMP_EDGE});

		rbo.create();
		rbo.allocate(size.x, size.y, Format::DEPTH);

		fbo.create();
		fbo.attachTexture(texture, Attachment::COLOR);
		fbo.attachRBO(rbo, Attachment::DEPTH);
		fbo.unbind();
	}

	ShaderProgram& PostProcess::getKernelShader()
	{
		return kernelShader;
	}

	Texture2D& PostProcess::getTexture()
	{
		return texture;
	}

	void PostProcess::useKernel(KernalType type)
	{
		mml::mat3 kernel;

		switch(type) {
			case KernalType::BLUR:
				kernel = mml::mat3(1 / 16.0f, 2 / 16.0f, 1 / 16.0f, 2 / 16.0f, 4 / 16.0f, 2 / 16.0f, 1 / 16.0f, 2 / 16.0f, 1 / 16.0f);
				break;
			case KernalType::SHARPEN:
				kernel = mml::mat3(1, 1, 1, 1, -8, 1, 1, 1, 1);
				break;
		}
		
		texture.bind();
		kernelShader.use();
		kernelShader.uniformInt(kernelShader.getUniform("tex"), 0);
		kernelShader.uniformMat3(kernelShader.getUniform("kernel"), kernel);
	}

	void PostProcess::startFrame() const
	{
		fbo.bind();
		fbo.clear(mgl::BufferBit::COLOR);
		fbo.clear(mgl::BufferBit::DEPTH);
		fbo.viewport(0, 0, texture.getWidth(), texture.getHeight());
	}

	void PostProcess::endFrame() const
	{
		fbo.unbind();
	}
}