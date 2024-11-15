#include <graphics/render/opengl/shaderprogram.hpp>

namespace mgl
{
	namespace gl
	{
		void ShaderProgram::create()
		{
			program.create();
		}

		void ShaderProgram::bind() const
		{
			program.bind();
		}

		void ShaderProgram::unbind() const
		{
			program.unbind();
		}

		void ShaderProgram::attachGLSLShadersFromFile(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath, const std::string& computePath) const
		{
			program.attachShaders(vertexPath, fragmentPath, geometryPath, computePath);
		}

		void ShaderProgram::attachGLSLShadersFromSrc(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc, const std::string& computeSrc) const
		{
			program.attachShaders(vertexSrc, fragmentSrc, geometrySrc, computeSrc);
		}

		void ShaderProgram::uniform(const std::string& loc, const mml::mat3& mat, bool transpose) const
		{
			program.uniformMat3(loc, mat, transpose);
		}
		
		void ShaderProgram::uniform(const std::string& loc, const mml::mat4& mat, bool transpose) const
		{
			program.uniformMat4(loc, mat, transpose);
		}
		
		void ShaderProgram::uniform(const std::string& loc, const mml::vec2& vec) const
		{
			program.uniformVec2(loc, vec);
		}
		
		void ShaderProgram::uniform(const std::string& loc, const mml::vec3& vec) const
		{
			program.uniformVec3(loc, vec);
		}
		
		void ShaderProgram::uniform(const std::string& loc, const mml::vec4& vec) const
		{
			program.uniformVec4(loc, vec);
		}
		
		void ShaderProgram::uniform(const std::string& loc, float v) const
		{
			program.uniformFloat(loc, v);
		}

		void ShaderProgram::uniform(const std::string& loc, int v) const
		{
			program.uniformInt(loc, v);
		}
		
		void ShaderProgram::uniform(const std::string& loc, uint v) const
		{
			program.uniformUint(loc, v);
		}


		void ShaderProgram::uniform(const std::string& loc, const std::vector<mml::mat3>& values, bool transpose) const
		{
			program.uniformMat3s(loc, values, transpose);
		}

		void ShaderProgram::uniforms(const std::string& loc, const std::vector<mml::mat4>& values, bool transpose) const
		{
			program.uniformMat4s(loc, values, transpose);
		}
		
		void ShaderProgram::uniforms(const std::string& loc, const std::vector<mml::vec2>& values) const
		{
			program.uniformVec2s(loc, values);
		}
		
		void ShaderProgram::uniforms(const std::string& loc, const std::vector<mml::vec3>& values) const
		{
			program.uniformVec3s(loc, values);
		}
		
		void ShaderProgram::uniforms(const std::string& loc, const std::vector<mml::vec4>& values) const
		{
			program.uniformVec4s(loc, values);
		}
		
		void ShaderProgram::uniforms(const std::string& loc, const std::vector<float>& values) const
		{
			program.uniformFloats(loc, values);
		}

		void ShaderProgram::uniforms(const std::string& loc, const std::vector<int>& values) const
		{
			program.uniformInts(loc, values);
		}
		
		void ShaderProgram::uniforms(const std::string& loc, const std::vector<uint>& values) const
		{
			program.uniformUints(loc, values);
		}
	}
}