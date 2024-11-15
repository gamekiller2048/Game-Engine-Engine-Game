#pragma once
#include <graphics/render/shadow.hpp>
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/opengl/cubemap.hpp>

namespace mgl
{
    class PointShadow : public Shadow
    {
    public:
        Cubemap cubemap;

        PointShadow(float bias=0.0005f, int sampleRadius=2);
        
        void create(const mml::uvec2& size, uint texUnit);
        void startFrame() const;
        void endFrame() const;
        void use(const Ref<Light>& light);
    };
}