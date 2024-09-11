#pragma once
#include <graphics/opengl/globject.hpp>

namespace mgl
{
	enum class ShaderType : GLuint
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
	
	enum class ShaderParam : GLuint
	{
		SHADER_TYPE = GL_SHADER_TYPE,
		DELETE_STATUS = GL_DELETE_STATUS,
		COMPILE_STATUS = GL_COMPILE_STATUS,
		LINK_STATUS = GL_LINK_STATUS,
		VALIDATE_STATUS = GL_VALIDATE_STATUS,
		INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH
	};

	class Shader : public GLObject
	{
	public:
		Shader(ShaderType type);
		Shader(Shader&& other) noexcept;
		~Shader();

		void create();
		void compile(const std::string& source, const std::string& _filePathError="<string>") const;
		void compileFromFile(const std::string& filePath) const;
		std::string getInfoLog() const;

		GLint getParameterInt(ShaderParam param) const;
	};

}