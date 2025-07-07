#pragma once
#include <graphics/render/rendercontext.hpp>
#include <graphics/render/texture2d.hpp>

namespace mgl
{
    class CubeMap
    {
    public:
        CubeMap(RenderContext* context);

        virtual void bindUnit() const = 0;
        virtual void unbind() const = 0;
        virtual void uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const = 0;

        virtual void loadFromFile(const std::array<std::string, 6>& filePaths) const = 0;
        virtual void allocate(uint width, uint height, TextureFormat format, TextureFormat internalFormat) const = 0;

    protected:
        RenderContext* context;
    };
}