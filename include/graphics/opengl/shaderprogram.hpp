#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glad/gl.h>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/enums.hpp>
#include <graphics/opengl/shader.hpp>
#include <graphics/opengl/computeshader.hpp>
#include <graphics/opengl/gltypes.hpp>

namespace mgl
{
    namespace gl
    {
        enum class ShaderProgramParam
        {
            DELETE_STATUS = GL_DELETE_STATUS,
            LINK_STATUS = GL_LINK_STATUS,
            VALIDATE_STATUS = GL_VALIDATE_STATUS,
            INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
            ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
            ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS,
            ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH,
            SHADER_SOURCE_LENGTH = GL_SHADER_SOURCE_LENGTH,
            ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
            ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
        };

        class ShaderProgram : public GLObject
        {
        public:
            ShaderProgram() = default;
            ShaderProgram(ShaderProgram&& other) noexcept;
            ~ShaderProgram();

            void create();
            void use() const;
            void unuse() const;

            GLint getParameterInt(ShaderProgramParam param) const;

            void attachShaders(const std::vector<Shader*>& shaders) const;
            void attachShadersFromFile(const std::string& vertexPath="", const std::string& fragmentPath="", const std::string& geometryPath="", const std::string& computeFilePath="") const;
            void attachShaders(const std::string& vertexSrc="", const std::string& fragmentSrc="", const std::string& geometrySrc="", const std::string& computeSrc="") const;
            std::string getInfoLog() const;

            void drawArrays(RenderPrimative primative, GLint first, GLsizei count) const;
            void drawElements(RenderPrimative primative, GLsizei count) const;
            void drawArraysInstanced(RenderPrimative primative, GLint first, GLsizei count, GLuint instances) const;
            void drawElementsInstanced(RenderPrimative primative, GLsizei count, GLuint instances) const;

            void compute(const GLuvec3& workGroups) const;
            void computeBarrier(MemoryBarrier barrier) const;

            GLuint getUniform(const std::string& loc) const;

            void uniformMat3(const std::string& loc, const GLmat3& mat, bool transpose=false) const;
            void uniformMat3s(const std::string& loc, const std::vector<GLmat3>& values, bool transpose=false) const;
            void uniformMat4(const std::string& loc, const GLmat4& mat, bool transpose = false) const;
            void uniformMat4s(const std::string& loc, const std::vector<GLmat4>& values, bool transpose=false) const;
            void uniformFloat(const std::string& loc, float v) const;
            void uniformFloats(const std::string& loc, const std::vector<float>& values) const;
            void uniformVec2(const std::string& loc, const GLvec2& vec) const;
            void uniformVec2s(const std::string& loc, const std::vector<GLvec2>& values) const;
            void uniformVec3(const std::string& loc, const GLvec3& vec) const;
            void uniformVec3s(const std::string& loc, const std::vector<GLvec3>& values) const;
            void uniformVec4(const std::string& loc, const GLvec4& vec) const;
            void uniformVec4s(const std::string& loc, const std::vector<GLvec4>& values) const;
            void uniformInt(const std::string& loc, int v) const;
            void uniformInts(const std::string& loc, const std::vector<int>& values) const;
            void uniformUint(const std::string& loc, uint v) const;
            void uniformUints(const std::string& loc, const std::vector<uint>& values) const;

            void uniformMat3(GLuint loc, const GLmat3& mat, bool transpose=false) const;
            void uniformMat3s(GLuint loc, const std::vector<GLmat3>& values, bool transpose=false) const;
            void uniformMat4(GLuint loc, const GLmat4& mat, bool transpose=false) const;
            void uniformMat4s(GLuint loc, const std::vector<GLmat4>& values, bool transpose=false) const;
            void uniformFloat(GLuint loc, float v) const;
            void uniformFloats(GLuint loc, const std::vector<float>& values) const;
            void uniformVec2(GLuint loc, const GLvec2& vec) const;
            void uniformVec2s(GLuint loc, const std::vector<GLvec2>& values) const;
            void uniformVec3(GLuint loc, const GLvec3& vec) const;
            void uniformVec3s(GLuint loc, const std::vector<GLvec3>& values) const;
            void uniformVec4(GLuint loc, const GLvec4& vec) const;
            void uniformVec4s(GLuint loc, const std::vector<GLvec4>& values) const;
            void uniformInt(GLuint loc, int v) const;
            void uniformInts(GLuint loc, const std::vector<int>& values) const;
            void uniformUint(GLuint loc, uint v) const;
            void uniformUints(GLuint loc, const std::vector<uint>& values) const;

        protected:
            mutable std::unordered_map<std::string, GLuint> cache;
        };
    }
}
