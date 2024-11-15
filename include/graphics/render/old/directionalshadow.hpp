#pragma once
#include <graphics/render/shadow.hpp>
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/opengl/texture.hpp>

namespace mgl
{
    class DirectionalShadow : public Shadow
    {
    public:
        Texture2D map;

        DirectionalShadow(float bias=0.0005f, int sampleRadius=2);

        void create(const mml::uvec2& size, uint texUnit);
        void startFrame() const;
        void endFrame() const;
        void use(const Ref<Light>& light);
    };
}
