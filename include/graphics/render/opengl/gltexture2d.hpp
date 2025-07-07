#pragma once
#include <graphics/render/texture2d.hpp>
#include <graphics/render/shaderprogram.hpp>

namespace mgl
{
    class GLTexture2DImpl;
    class GLTexture2D : public Texture2D
    {
    public:
        GLTexture2D(RenderContext* context);
        ~GLTexture2D();

        GLTexture2DImpl* getImpl() const;

        void bindUnit() const;
        void bindImage(uint unit, uint level, Access access) const;
        void unbind() const;
        void uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const;
        void loadFromFile(const std::string& filePath) const;
        void allocate(uint width, uint height, TextureFormat format, TextureFormat internalFormat) const;

    protected:
        Owned<GLTexture2DImpl> impl;
    };
}