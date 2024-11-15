#pragma once
#include <vector>
#include <math/math.hpp>
#include <graphics/opengl/program.hpp>
#include <graphics/render/shaderprogram.hpp>

namespace mgl
{
    namespace gl
    {
        class ShaderProgram : public mgl::ShaderProgram
        {
        public:
            void create();
            void bind() const;
            void unbind() const;

            void attachGLSLShadersFromFile(const std::string& vertexPath = "", const std::string& fragmentPath = "", const std::string& geometryPath = "", const std::string& computePath = "") const;
            void attachGLSLShadersFromSrc(const std::string& vertexSrc = "", const std::string& fragmentSrc = "", const std::string& geometrySrc = "", const std::string& computeSrc = "") const;

            void uniform(const std::string& loc, const mml::mat3& mat, bool transpose = false) const;
            void uniform(const std::string& loc, const mml::mat4& mat, bool transpose = false) const;
            void uniform(const std::string& loc, float v) const;
            void uniform(const std::string& loc, const mml::vec2& vec) const;
            void uniform(const std::string& loc, const mml::vec3& vec) const;
            void uniform(const std::string& loc, const mml::vec4& vec) const;
            void uniform(const std::string& loc, int v) const;
            void uniform(const std::string& loc, uint v) const;

            void uniform(const std::string& loc, const std::vector<mml::mat3>& values, bool transpose = false) const;
            void uniforms(const std::string& loc, const std::vector<mml::mat4>& values, bool transpose = false) const;
            void uniforms(const std::string& loc, const std::vector<mml::vec2>& values) const;
            void uniforms(const std::string& loc, const std::vector<mml::vec3>& values) const;
            void uniforms(const std::string& loc, const std::vector<mml::vec4>& values) const;
            void uniforms(const std::string& loc, const std::vector<float>& values) const;
            void uniforms(const std::string& loc, const std::vector<int>& values) const;
            void uniforms(const std::string& loc, const std::vector<uint>& values) const;
        
        protected:
            Program program;
        };
    }
}