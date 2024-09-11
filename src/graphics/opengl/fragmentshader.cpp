#include <graphics/opengl/fragmentshader.hpp>

namespace mgl
{
	FragmentShader::FragmentShader() :
		Shader(ShaderType::FRAGMENT) {}

	FragmentShader::FragmentShader(FragmentShader&& other) noexcept :
		Shader(std::move(other)) {}
}