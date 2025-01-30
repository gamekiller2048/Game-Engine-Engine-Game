#include <graphics/render/opengl/glshaderprogram.hpp>
#include "glshaderprogramimpl.hpp"

namespace mgl
{
	GLShaderProgram::GLShaderProgram(RenderContext* context) :
		ShaderProgram(context), impl(CreateOwned<GLShaderProgramImpl>()) {}

	GLShaderProgram::~GLShaderProgram() = default;

	GLShaderProgramImpl* GLShaderProgram::getImpl() const
	{
		return impl.get();
	}


	void GLShaderProgram::create()
	{
		impl->program.create();
	}
	
	void GLShaderProgram::bind() const
	{
		impl->program.bind();
	}

	void GLShaderProgram::unbind() const
	{
		impl->program.unbind();
	}

	void GLShaderProgram::attachGLSLShadersFromFile(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath, const std::string& computePath) const
	{
		impl->program.attachShaders(vertexPath, fragmentPath, geometryPath, computePath);
	}

	void GLShaderProgram::attachGLSLShadersFromSrc(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc, const std::string& computeSrc) const
	{
		impl->program.attachShaders(vertexSrc, fragmentSrc, geometrySrc, computeSrc);
	}

	void GLShaderProgram::drawArrays(uint startIndex, uint vertexCount) const
	{
		impl->program.drawArrays(gl::RenderPrimative::TRIANGLES, 0, vertexCount);
	}

	void GLShaderProgram::drawElements(uint indiceCount) const
	{
		impl->program.drawElements(gl::RenderPrimative::TRIANGLES, indiceCount);
	}

	void GLShaderProgram::uniform(const std::string& loc, const mml::mat3& mat, bool transpose) const
	{
		impl->program.uniformMat3(loc, mat, transpose);
	}
		
	void GLShaderProgram::uniform(const std::string& loc, const mml::mat4& mat, bool transpose) const
	{
		impl->program.uniformMat4(loc, mat, transpose);
	}
		
	void GLShaderProgram::uniform(const std::string& loc, const mml::vec2& vec) const
	{
		impl->program.uniformVec2(loc, vec);
	}
		
	void GLShaderProgram::uniform(const std::string& loc, const mml::vec3& vec) const
	{
		impl->program.uniformVec3(loc, vec);
	}
		
	void GLShaderProgram::uniform(const std::string& loc, const mml::vec4& vec) const
	{
		impl->program.uniformVec4(loc, vec);
	}
		
	void GLShaderProgram::uniform(const std::string& loc, float v) const
	{
		impl->program.uniformFloat(loc, v);
	}

	void GLShaderProgram::uniform(const std::string& loc, int v) const
	{
		impl->program.uniformInt(loc, v);
	}
		
	void GLShaderProgram::uniform(const std::string& loc, uint v) const
	{
		impl->program.uniformUint(loc, v);
	}


	void GLShaderProgram::uniform(const std::string& loc, const std::vector<mml::mat3>& values, bool transpose) const
	{
		impl->program.uniformMat3s(loc, values, transpose);
	}

	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<mml::mat4>& values, bool transpose) const
	{
		impl->program.uniformMat4s(loc, values, transpose);
	}
		
	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<mml::vec2>& values) const
	{
		impl->program.uniformVec2s(loc, values);
	}
		
	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<mml::vec3>& values) const
	{
		impl->program.uniformVec3s(loc, values);
	}
		
	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<mml::vec4>& values) const
	{
		impl->program.uniformVec4s(loc, values);
	}
		
	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<float>& values) const
	{
		impl->program.uniformFloats(loc, values);
	}

	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<int>& values) const
	{
		impl->program.uniformInts(loc, values);
	}
		
	void GLShaderProgram::uniforms(const std::string& loc, const std::vector<uint>& values) const
	{
		impl->program.uniformUints(loc, values);
	}
}