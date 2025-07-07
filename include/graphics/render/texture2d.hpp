#pragma once
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
    enum class TextureFormat
    {
        RGB,
        RGB32F,
        RGBA,
        RGBA32F,
        DEPTH
    };

    class Texture2D
    {
    public:
        Texture2D(RenderContext* context);

        virtual void bindUnit() const = 0;
        virtual void bindImage(uint unit, uint level, Access access) const = 0;
        virtual void unbind() const = 0;
        virtual void uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const = 0;

        virtual void loadFromFile(const std::string& filePath) const = 0;
        virtual void allocate(uint width, uint height, TextureFormat format, TextureFormat internalFormat) const = 0;

    protected:
        RenderContext* context;
    };
}