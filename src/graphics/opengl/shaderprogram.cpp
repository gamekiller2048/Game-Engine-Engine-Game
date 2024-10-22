#include <graphics/opengl/shaderprogram.hpp>
#include <fstream>
#include <graphics/opengl/vertexshader.hpp>
#include <graphics/opengl/fragmentshader.hpp>
#include <graphics/opengl/geometryshader.hpp>
#include <graphics/opengl/glcontext.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        ShaderProgram::~ShaderProgram()
        {
            if(id) GL_CALL(glDeleteProgram, id);
        }

        ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept :
            GLObject(std::move(other)) {}

        void ShaderProgram::create()
        {
            id = GL_CALLV(glCreateProgram);
        }

        void ShaderProgram::use() const
        {
            GL_CALL(glUseProgram, id);
        }

        void ShaderProgram::unuse() const
        {
            GL_CALL(glUseProgram, 0);
        }

        GLint ShaderProgram::getParameterInt(ShaderProgramParam param) const
        {
            GLint result;
            GL_CALL(glGetProgramiv, id, (GLenum)param, &result);
            return result;
        }

        void ShaderProgram::attachShaders(const std::vector<Shader*>& shaders) const
        {
            for(const Shader* shader : shaders)
                GL_CALL(glAttachShader, id, shader->getID());

            GL_CALL(glLinkProgram, id);
            GL_CALL(glValidateProgram, id);

            for(const Shader* shader : shaders)
                GL_CALL(glDetachShader, id, shader->getID());
        }

        void ShaderProgram::attachShadersFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryFilePath, const std::string& computeFilePath) const
        {
            VertexShader vertexShader;
            if(!vertexFilePath.empty()) {
                vertexShader.create();
                vertexShader.compileFromFile(vertexFilePath);
                GL_CALL(glAttachShader, id, vertexShader.getID());
            }

            FragmentShader fragmentShader;
            if(!fragmentFilePath.empty()) {
                fragmentShader.create();
                fragmentShader.compileFromFile(fragmentFilePath);
                GL_CALL(glAttachShader, id, fragmentShader.getID());
            }

            GeometryShader geometryShader;
            if(!geometryFilePath.empty()) {
                geometryShader.create();
                geometryShader.compileFromFile(geometryFilePath);
                GL_CALL(glAttachShader, id, geometryShader.getID());
            }

            ComputeShader computeShader;
            if(!computeFilePath.empty()) {
                computeShader.create();
                computeShader.compileFromFile(computeFilePath);
                GL_CALL(glAttachShader, id, computeShader.getID());
            }

            GL_CALL(glLinkProgram, id);
            if(!getParameterInt(ShaderProgramParam::LINK_STATUS))
                MLL_DEBUG(GLSLError(getInfoLog(), "LINKING"));

            //if(!getParameterInt(ShaderProgramParam::VALIDATE_STATUS))
                //METAL_ERROR(GLSLError(getInfoLog(), "VALIDATE"));

            if(vertexShader.getID()) GL_CALL(glDetachShader, id, vertexShader.getID());
            if(fragmentShader.getID()) GL_CALL(glDetachShader, id, fragmentShader.getID());
            if(geometryShader.getID()) GL_CALL(glDetachShader, id, geometryShader.getID());
            if(computeShader.getID()) GL_CALL(glDetachShader, id, computeShader.getID());
        }

        void ShaderProgram::attachShaders(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc, const std::string& computeSrc) const
        {
            VertexShader vertexShader;
            if(!vertexSrc.empty()) {
                vertexShader.create();
                vertexShader.compile(vertexSrc);
                GL_CALL(glAttachShader, id, vertexShader.getID());
            }

            FragmentShader fragmentShader;
            if(!fragmentSrc.empty()) {
                fragmentShader.create();
                fragmentShader.compile(fragmentSrc);
                GL_CALL(glAttachShader, id, fragmentShader.getID());
            }

            GeometryShader geometryShader;
            if(!geometrySrc.empty()) {
                geometryShader.create();
                geometryShader.compile(geometrySrc);
                GL_CALL(glAttachShader, id, geometryShader.getID());
            }

            ComputeShader computeShader;
            if(!computeSrc.empty()) {
                computeShader.create();
                computeShader.compile(computeSrc);
                GL_CALL(glAttachShader, id, computeShader.getID());
            }

            GL_CALL(glLinkProgram, id);

            if(!getParameterInt(ShaderProgramParam::LINK_STATUS))
                MLL_DEBUG(GLSLError(getInfoLog(), "LINKING"));

            //if(!getParameterInt(ShaderProgramParam::VALIDATE_STATUS))
            //    METAL_ERROR(GLSLError(getInfoLog(), "VALIDATE"));

            if(vertexShader.getID()) GL_CALL(glDetachShader, id, vertexShader.getID());
            if(fragmentShader.getID()) GL_CALL(glDetachShader, id, fragmentShader.getID());
            if(geometryShader.getID()) GL_CALL(glDetachShader, id, geometryShader.getID());
            if(computeShader.getID()) GL_CALL(glDetachShader, id, computeShader.getID());
        }

        std::string ShaderProgram::getInfoLog() const
        {
            GLint length = getParameterInt(ShaderProgramParam::INFO_LOG_LENGTH);
            GLchar* message = (GLchar*)alloca(length);

            GL_CALL(glGetProgramInfoLog, id, length, &length, message);

            return std::string(message);
        }
        void ShaderProgram::drawArrays(RenderPrimative primative, GLint first, GLsizei count) const
        {
            GL_CALL(glDrawArrays, (GLenum)primative, first, count);
        }

        void ShaderProgram::drawElements(RenderPrimative primative, GLsizei count) const
        {
            GL_CALL(glDrawElements, (GLenum)primative, count, GL_UNSIGNED_INT, 0);
        }

        void ShaderProgram::drawArraysInstanced(RenderPrimative primative, GLint first, GLsizei count, GLuint instances) const
        {
            GL_CALL(glDrawArraysInstanced, (GLenum)primative, first, count, instances);
        }

        void ShaderProgram::drawElementsInstanced(RenderPrimative primative, GLsizei count, GLuint instances) const
        {
            GL_CALL(glDrawElementsInstanced, (GLenum)primative, count, GL_UNSIGNED_INT, 0, instances);
        }

        void ShaderProgram::compute(const GLuvec3& workGroups) const
        {
            use();
            GL_CALL(glDispatchCompute, workGroups.x, workGroups.y, workGroups.z);
        }

        void ShaderProgram::computeBarrier(MemoryBarrier barrier) const
        {
            GL_CALL(glMemoryBarrier, (GLenum)barrier);
        }

        GLuint ShaderProgram::getUniform(const std::string& loc) const
        {
            if(cache.find(loc) == cache.end()) {
                GLint i = GL_CALLV(glGetUniformLocation, id, loc.c_str());

                if(i == -1)
                    MLL_DEBUG(GLError("invalid uniform " + loc));

                cache[loc] = i;
                return i;
            }
            return cache[loc];
        }

        void ShaderProgram::uniformMat3(const std::string& loc, const GLmat3& mat, bool transpose) const
        {
            uniformMat3(getUniform(loc), mat, transpose);
        }

        void ShaderProgram::uniformMat3s(const std::string& loc, const std::vector<GLmat3>& values, bool transpose) const
        {
            uniformMat3s(getUniform(loc), values, transpose);
        }

        void ShaderProgram::uniformMat4(const std::string& loc, const GLmat4& mat, bool transpose) const
        {
            uniformMat4(getUniform(loc), mat, transpose);
        }

        void ShaderProgram::uniformMat4s(const std::string& loc, const std::vector<GLmat4>& values, bool transpose) const
        {
            uniformMat4s(getUniform(loc), values, transpose);
        }

        void ShaderProgram::uniformFloat(const std::string& loc, float v) const
        {
            uniformFloat(getUniform(loc), v);
        }

        void ShaderProgram::uniformFloats(const std::string& loc, const std::vector<float>& values) const
        {
            uniformFloats(getUniform(loc), values);
        }

        void ShaderProgram::uniformVec2(const std::string& loc, const GLvec2& vec) const
        {
            uniformVec2(getUniform(loc), vec);
        }

        void ShaderProgram::uniformVec2s(const std::string& loc, const std::vector<GLvec2>& values) const
        {
            uniformVec2s(getUniform(loc), values);
        }

        void ShaderProgram::uniformVec3(const std::string& loc, const GLvec3& vec) const
        {
            uniformVec3(getUniform(loc), vec);
        }

        void ShaderProgram::uniformVec3s(const std::string& loc, const std::vector<GLvec3>& values) const
        {
            uniformVec3s(getUniform(loc), values);
        }

        void ShaderProgram::uniformVec4(const std::string& loc, const GLvec4& vec) const
        {
            uniformVec4(getUniform(loc), vec);
        }

        void ShaderProgram::uniformVec4s(const std::string& loc, const std::vector<GLvec4>& values) const
        {
            uniformVec4s(getUniform(loc), values);
        }

        void ShaderProgram::uniformInt(const std::string& loc, int v) const
        {
            uniformInt(getUniform(loc), v);
        }

        void ShaderProgram::uniformInts(const std::string& loc, const std::vector<int>& values) const
        {
            uniformInts(getUniform(loc), values);
        }

        void ShaderProgram::uniformUint(const std::string& loc, uint v) const
        {
            uniformUint(getUniform(loc), v);
        }

        void ShaderProgram::uniformUints(const std::string& loc, const std::vector<uint>& values) const
        {
            uniformUints(getUniform(loc), values);
        }

        void ShaderProgram::uniformMat3(GLuint loc, const GLmat3& mat, bool transpose) const
        {
            GL_CALL(glUniformMatrix3fv, loc, 1, transpose, (GLfloat*)&mat);
        }

        void ShaderProgram::uniformMat3s(GLuint loc, const std::vector<GLmat3>& values, bool transpose) const
        {
            GL_CALL(glUniformMatrix3fv, loc, values.size(), transpose, (GLfloat*)values.data());
        }

        void ShaderProgram::uniformMat4(GLuint loc, const GLmat4& mat, bool transpose) const
        {
            GL_CALL(glUniformMatrix4fv, loc, 1, transpose, (GLfloat*)&mat);
        }

        void ShaderProgram::uniformMat4s(GLuint loc, const std::vector<GLmat4>& values, bool transpose) const
        {
            GL_CALL(glUniformMatrix4fv, loc, values.size(), transpose, (GLfloat*)values.data());
        }

        void ShaderProgram::uniformFloat(GLuint loc, float v) const
        {
            GL_CALL(glUniform1f, loc, v);
        }

        void ShaderProgram::uniformFloats(GLuint loc, const std::vector<float>& values) const
        {
            GL_CALL(glUniform1fv, loc, values.size(), values.data());
        }

        void ShaderProgram::uniformVec2(GLuint loc, const GLvec2& vec) const
        {
            GL_CALL(glUniform2fv, loc, 1, (GLfloat*)&vec);
        }

        void ShaderProgram::uniformVec2s(GLuint loc, const std::vector<GLvec2>& values) const
        {
            GL_CALL(glUniform3fv, loc, values.size(), (GLfloat*)values.data());
        }

        void ShaderProgram::uniformVec3(GLuint loc, const GLvec3& vec) const
        {
            GL_CALL(glUniform3fv, loc, 1, (GLfloat*)&vec);
        }

        void ShaderProgram::uniformVec3s(GLuint loc, const std::vector<GLvec3>& values) const
        {
            GL_CALL(glUniform3fv, loc, values.size(), (GLfloat*)values.data());
        }

        void ShaderProgram::uniformVec4(GLuint loc, const GLvec4& vec) const
        {
            GL_CALL(glUniform4fv, loc, 1, (GLfloat*)&vec);
        }

        void ShaderProgram::uniformVec4s(GLuint loc, const std::vector<GLvec4>& values) const
        {
            GL_CALL(glUniform4fv, loc, values.size(), (GLfloat*)values.data());
        }

        void ShaderProgram::uniformInt(GLuint loc, int v) const
        {
            GL_CALL(glUniform1i, loc, v);
        }

        void ShaderProgram::uniformInts(GLuint loc, const std::vector<int>& values) const
        {
            GL_CALL(glUniform1iv, loc, values.size(), values.data());
        }

        void ShaderProgram::uniformUint(GLuint loc, uint v) const
        {
            GL_CALL(glUniform1ui, loc, v);
        }

        void ShaderProgram::uniformUints(GLuint loc, const std::vector<uint>& values) const
        {
            GL_CALL(glUniform1uiv, loc, values.size(), values.data());
        }
    }
}
