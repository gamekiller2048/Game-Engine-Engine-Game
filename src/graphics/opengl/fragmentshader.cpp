#include <graphics/opengl/fragmentshader.hpp>

namespace mgl
{
	namespace gl
	{
		FragmentShader::FragmentShader() :
			Shader(ShaderType::FRAGMENT) {}

		FragmentShader::FragmentShader(FragmentShader&& other) noexcept :
			Shader(std::move(other)) {}
	}
}