#include <graphics/opengl/program.hpp>
#include <fstream>
#include <graphics/opengl/vertexshader.hpp>
#include <graphics/opengl/fragmentshader.hpp>
#include <graphics/opengl/geometryshader.hpp>
#include <graphics/opengl/context.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        Program::~Program()
        {
            if(id) GL_CALL(glDeleteProgram, id);
        }

        Program::Program(Program&& other) noexcept :
            GLObject(std::move(other)) {}

        void Program::create()
        {
            id = GL_CALLV(glCreateProgram);
        }

        void Program::bind() const
        {
            GL_CALL(glUseProgram, id);
        }

        void Program::unbind() const
        {
            GL_CALL(glUseProgram, 0);
        }

        GLint Program::getParameterInt(ProgramParam param) const
        {
            GLint result;
            GL_CALL(glGetProgramiv, id, (GLenum)param, &result);
            return result;
        }

        void Program::attachShaders(const std::vector<Shader*>& shaders) const
        {
            for(const Shader* shader : shaders)
                GL_CALL(glAttachShader, id, shader->getID());

            GL_CALL(glLinkProgram, id);
            GL_CALL(glValidateProgram, id);

            for(const Shader* shader : shaders)
                GL_CALL(glDetachShader, id, shader->getID());
        }

        void Program::attachShadersFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryFilePath, const std::string& computeFilePath) const
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
            if(!getParameterInt(ProgramParam::LINK_STATUS))
                MLL_DEBUG(GLSLError(getInfoLog(), "LINKING"));

            //if(!getParameterInt(ProgramParam::VALIDATE_STATUS))
                //METAL_ERROR(GLSLError(getInfoLog(), "VALIDATE"));

            if(vertexShader.getID()) GL_CALL(glDetachShader, id, vertexShader.getID());
            if(fragmentShader.getID()) GL_CALL(glDetachShader, id, fragmentShader.getID());
            if(geometryShader.getID()) GL_CALL(glDetachShader, id, geometryShader.getID());
            if(computeShader.getID()) GL_CALL(glDetachShader, id, computeShader.getID());
        }

        void Program::attachShaders(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc, const std::string& computeSrc) const
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

            if(!getParameterInt(ProgramParam::LINK_STATUS))
                MLL_DEBUG(GLSLError(getInfoLog(), "LINKING"));

            //if(!getParameterInt(ProgramParam::VALIDATE_STATUS))
            //    METAL_ERROR(GLSLError(getInfoLog(), "VALIDATE"));

            if(vertexShader.getID()) GL_CALL(glDetachShader, id, vertexShader.getID());
            if(fragmentShader.getID()) GL_CALL(glDetachShader, id, fragmentShader.getID());
            if(geometryShader.getID()) GL_CALL(glDetachShader, id, geometryShader.getID());
            if(computeShader.getID()) GL_CALL(glDetachShader, id, computeShader.getID());
        }

        std::string Program::getInfoLog() const
        {
            GLint length = getParameterInt(ProgramParam::INFO_LOG_LENGTH);
            GLchar* message = (GLchar*)alloca(length);

            GL_CALL(glGetProgramInfoLog, id, length, &length, message);

            return std::string(message);
        }
        void Program::drawArrays(RenderPrimative primative, GLint first, GLsizei count) const
        {
            GL_CALL(glDrawArrays, (GLenum)primative, first, count);
        }

        void Program::drawElements(RenderPrimative primative, GLsizei count) const
        {
            GL_CALL(glDrawElements, (GLenum)primative, count, GL_UNSIGNED_INT, 0);
        }

        void Program::drawArraysInstanced(RenderPrimative primative, GLint first, GLsizei count, GLuint instances) const
        {
            GL_CALL(glDrawArraysInstanced, (GLenum)primative, first, count, instances);
        }

        void Program::drawElementsInstanced(RenderPrimative primative, GLsizei count, GLuint instances) const
        {
            GL_CALL(glDrawElementsInstanced, (GLenum)primative, count, GL_UNSIGNED_INT, 0, instances);
        }

        void Program::compute(const GLuvec3& workGroups) const
        {
            GL_CALL(glDispatchCompute, workGroups.x, workGroups.y, workGroups.z);
        }

        void Program::computeBarrier(MemoryBarrier barrier) const
        {
            GL_CALL(glMemoryBarrier, (GLenum)barrier);
        }

        GLuint Program::getUniform(const std::string& loc) const
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

        void Program::uniformMat3(const std::string& loc, const GLmat3& mat, bool transpose) const
        {
            uniformMat3(getUniform(loc), mat, transpose);
        }

        void Program::uniformMat3s(const std::string& loc, const std::vector<GLmat3>& values, bool transpose) const
        {
            uniformMat3s(getUniform(loc), values, transpose);
        }

        void Program::uniformMat4(const std::string& loc, const GLmat4& mat, bool transpose) const
        {
            uniformMat4(getUniform(loc), mat, transpose);
        }

        void Program::uniformMat4s(const std::string& loc, const std::vector<GLmat4>& values, bool transpose) const
        {
            uniformMat4s(getUniform(loc), values, transpose);
        }

        void Program::uniformFloat(const std::string& loc, float v) const
        {
            uniformFloat(getUniform(loc), v);
        }

        void Program::uniformFloats(const std::string& loc, const std::vector<float>& values) const
        {
            uniformFloats(getUniform(loc), values);
        }

        void Program::uniformVec2(const std::string& loc, const GLvec2& vec) const
        {
            uniformVec2(getUniform(loc), vec);
        }

        void Program::uniformVec2s(const std::string& loc, const std::vector<GLvec2>& values) const
        {
            uniformVec2s(getUniform(loc), values);
        }

        void Program::uniformVec3(const std::string& loc, const GLvec3& vec) const
        {
            uniformVec3(getUniform(loc), vec);
        }

        void Program::uniformVec3s(const std::string& loc, const std::vector<GLvec3>& values) const
        {
            uniformVec3s(getUniform(loc), values);
        }

        void Program::uniformVec4(const std::string& loc, const GLvec4& vec) const
        {
            uniformVec4(getUniform(loc), vec);
        }

        void Program::uniformVec4s(const std::string& loc, const std::vector<GLvec4>& values) const
        {
            uniformVec4s(getUniform(loc), values);
        }

        void Program::uniformInt(const std::string& loc, int v) const
        {
            uniformInt(getUniform(loc), v);
        }

        void Program::uniformInts(const std::string& loc, const std::vector<int>& values) const
        {
            uniformInts(getUniform(loc), values);
        }

        void Program::uniformUint(const std::string& loc, uint v) const
        {
            uniformUint(getUniform(loc), v);
        }

        void Program::uniformUints(const std::string& loc, const std::vector<uint>& values) const
        {
            uniformUints(getUniform(loc), values);
        }

        void Program::uniformMat3(GLuint loc, const GLmat3& mat, bool transpose) const
        {
            GL_CALL(glUniformMatrix3fv, loc, 1, transpose, (GLfloat*)&mat);
        }

        void Program::uniformMat3s(GLuint loc, const std::vector<GLmat3>& values, bool transpose) const
        {
            GL_CALL(glUniformMatrix3fv, loc, values.size(), transpose, (GLfloat*)values.data());
        }

        void Program::uniformMat4(GLuint loc, const GLmat4& mat, bool transpose) const
        {
            GL_CALL(glUniformMatrix4fv, loc, 1, transpose, (GLfloat*)&mat);
        }

        void Program::uniformMat4s(GLuint loc, const std::vector<GLmat4>& values, bool transpose) const
        {
            GL_CALL(glUniformMatrix4fv, loc, values.size(), transpose, (GLfloat*)values.data());
        }

        void Program::uniformFloat(GLuint loc, float v) const
        {
            GL_CALL(glUniform1f, loc, v);
        }

        void Program::uniformFloats(GLuint loc, const std::vector<float>& values) const
        {
            GL_CALL(glUniform1fv, loc, values.size(), values.data());
        }

        void Program::uniformVec2(GLuint loc, const GLvec2& vec) const
        {
            GL_CALL(glUniform2fv, loc, 1, (GLfloat*)&vec);
        }

        void Program::uniformVec2s(GLuint loc, const std::vector<GLvec2>& values) const
        {
            GL_CALL(glUniform3fv, loc, values.size(), (GLfloat*)values.data());
        }

        void Program::uniformVec3(GLuint loc, const GLvec3& vec) const
        {
            GL_CALL(glUniform3fv, loc, 1, (GLfloat*)&vec);
        }

        void Program::uniformVec3s(GLuint loc, const std::vector<GLvec3>& values) const
        {
            GL_CALL(glUniform3fv, loc, values.size(), (GLfloat*)values.data());
        }

        void Program::uniformVec4(GLuint loc, const GLvec4& vec) const
        {
            GL_CALL(glUniform4fv, loc, 1, (GLfloat*)&vec);
        }

        void Program::uniformVec4s(GLuint loc, const std::vector<GLvec4>& values) const
        {
            GL_CALL(glUniform4fv, loc, values.size(), (GLfloat*)values.data());
        }

        void Program::uniformInt(GLuint loc, int v) const
        {
            GL_CALL(glUniform1i, loc, v);
        }

        void Program::uniformInts(GLuint loc, const std::vector<int>& values) const
        {
            GL_CALL(glUniform1iv, loc, values.size(), values.data());
        }

        void Program::uniformUint(GLuint loc, uint v) const
        {
            GL_CALL(glUniform1ui, loc, v);
        }

        void Program::uniformUints(GLuint loc, const std::vector<uint>& values) const
        {
            GL_CALL(glUniform1uiv, loc, values.size(), values.data());
        }
    }
}
