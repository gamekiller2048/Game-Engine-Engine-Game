#pragma once
#include <math/math.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/texture2d.hpp>
#include <graphics/render/rendercontext.hpp>
#include <graphics/render/shadervariant.hpp>

namespace mgl
{
    struct Material
    {
        Ref<ShaderProgram> shader;
        RenderContext* context;

        Material(RenderContext* context);
        virtual void use() const = 0;
    };

    struct BasicMaterial : public Material
    {
        mml::color albedo;

        BasicMaterial(RenderContext* context, const BasicShaderVariant& shaderVariant);
        void use() const;
    };

    struct StandardMaterial : public Material
    {
        Ref<Texture2D> diffuseMap;
        Ref<Texture2D> normalMap;
        Ref<Texture2D> specularMap;
        mml::color albedo;

        StandardShaderVariant shaderVariant;

        StandardMaterial(RenderContext* context, const StandardShaderVariant& shaderVariant);
        void use() const;
    };
}