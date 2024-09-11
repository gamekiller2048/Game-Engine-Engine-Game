#include <graphics/opengl/vertexshader.hpp>

namespace mgl
{
	VertexShader::VertexShader() :
		Shader(ShaderType::VERTEX) {}

	VertexShader::VertexShader(VertexShader&& other) noexcept :
		Shader(std::move(other)) {}
}