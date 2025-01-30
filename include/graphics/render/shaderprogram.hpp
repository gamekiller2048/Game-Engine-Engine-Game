#pragma once
#include <vector>
#include <math/math.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
	class ShaderProgram
	{
	public:
        ShaderProgram(RenderContext* context);

        virtual void create() = 0;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void attachGLSLShadersFromFile(const std::string& vertexPath = "", const std::string& fragmentPath = "", const std::string& geometryPath = "", const std::string& computeFilePath = "") const = 0;
        virtual void attachGLSLShadersFromSrc(const std::string& vertexSrc = "", const std::string& fragmentSrc = "", const std::string& geometrySrc = "", const std::string& computeSrc = "") const = 0;

        virtual void drawArrays(uint startIndex, uint vertexCount) const = 0;
        virtual void drawElements(uint indiceCount) const = 0;

        virtual void uniform(const std::string& loc, const mml::mat3& mat, bool transpose = false) const = 0;
        virtual void uniform(const std::string& loc, const mml::mat4& mat, bool transpose = false) const = 0;
        virtual void uniform(const std::string& loc, float v) const = 0;
        virtual void uniform(const std::string& loc, const mml::vec2& vec) const = 0;
        virtual void uniform(const std::string& loc, const mml::vec3& vec) const = 0;
        virtual void uniform(const std::string& loc, const mml::vec4& vec) const = 0;
        virtual void uniform(const std::string& loc, int v) const = 0;
        virtual void uniform(const std::string& loc, uint v) const = 0;

        virtual void uniform(const std::string& loc, const std::vector<mml::mat3>& values, bool transpose = false) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<mml::mat4>& values, bool transpose = false) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<mml::vec2>& values) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<mml::vec3>& values) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<mml::vec4>& values) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<float>& values) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<int>& values) const = 0;
        virtual void uniforms(const std::string& loc, const std::vector<uint>& values) const = 0;
    
    protected:
        RenderContext* context;
    };
}