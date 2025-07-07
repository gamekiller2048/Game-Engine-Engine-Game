#pragma once

namespace mgl
{
    enum class RenderPipeline
    {
        FORWARD,
        DEFERRED
    };

    class ShaderVariant
    {
    public:
        std::string srcVert;
        std::string srcFrag;
        uint version;

        ShaderVariant(uint version);
    };

    class StandardShaderVariant : public ShaderVariant
    {
    public:
        RenderPipeline pipeline;
        bool diffuseMap;
        bool normalMap;
        bool specularMap;
        uint numDirLights;
        uint numPointLights;

        StandardShaderVariant(RenderPipeline pipeline, bool diffuseMap, bool normalMap, bool specularMap, uint numDirLights, uint numPointLights, uint version=440);
    };

    class BasicShaderVariant : public ShaderVariant
    {
    public:
        BasicShaderVariant(uint version=440);
    };
}