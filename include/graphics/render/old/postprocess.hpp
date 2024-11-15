#pragma once
#include <math/math.hpp>
#include <graphics/opengl/fbo.hpp>

namespace mgl
{
	enum class KernalType
	{
		BLUR,
		SHARPEN
	};

	class PostProcess
	{
	public:
		void createKernelShader();
		void create(const mml::uvec2& size);

		ShaderProgram& getKernelShader();
		Texture2D& getTexture();

		void useKernel(KernalType type);
		void startFrame() const;
		void endFrame() const;

	
	protected:
		FBO fbo;
		RBO rbo;
		Texture2D texture;

		ShaderProgram kernelShader;
	};
}

