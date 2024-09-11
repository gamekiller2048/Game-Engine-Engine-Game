#include <graphics/opengl/shader.hpp>
#include <fstream>
#include <string>
#include <resourceloader/resourceloader.hpp>
#include "errorcheck.hpp"

namespace mgl
{
	Shader::Shader(ShaderType type) :
		GLObject((GLenum)type) {}

    Shader::Shader(Shader&& other) noexcept :
        GLObject(std::move(other)) {}

    Shader::~Shader()
    {
        GL_CALL(glDeleteShader, id);
    }

    void Shader::create()
    {
        id = GL_CALLV(glCreateShader, gltype);
    }

    void Shader::compile(const std::string& source, const std::string& _filePathError) const
    {
        const char* src = source.c_str();
        GL_CALL(glShaderSource, id, 1, &src, NULL);
        GL_CALL(glCompileShader, id);

        if(!getParameterInt(ShaderParam::COMPILE_STATUS))
            MLL_DEBUG(GLSLError(getInfoLog(), _filePathError));
    }
    
    void Shader::compileFromFile(const std::string& filePath) const
    {
        compile(mrl::ResourceLoader::read(filePath), filePath);
    }

    std::string Shader::getInfoLog() const
    {
        GLint length = getParameterInt(ShaderParam::INFO_LOG_LENGTH);
        GLchar* message = (GLchar*)alloca(length);

        GL_CALL(glGetShaderInfoLog, id, length, &length, message);

        return std::string(message);
    }

    GLint Shader::getParameterInt(ShaderParam param) const
    {
        GLint result;
        GL_CALL(glGetShaderiv, id, (GLenum)param, &result);
        return result;
    }
}