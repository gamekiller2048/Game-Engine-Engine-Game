#pragma once
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/core/resource.hpp>
#include <graphics/opengl/fbo.hpp>

namespace mgl
{
    class ModelMesh;
    class Light;

    class Shadow
    {
    public:
        mml::uvec2 size;
        float bias;
        int sampleRadius;
        
        FBO fbo;
        ShaderProgram shader;

        Shadow(float bias, int sampleRadius);

        virtual void create(const mml::uvec2& size, uint texUnit) = 0;
        virtual void startFrame() const = 0;
        virtual void endFrame() const = 0;
        virtual void use(const Ref<Light>& light) = 0;
        void useMeshTransform(const Ref<ModelMesh>& mesh);
    };
}
