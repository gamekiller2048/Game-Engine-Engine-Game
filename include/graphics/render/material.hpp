#pragma once
#include <math/math.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/texture2d.hpp>
#include  <graphics/render/rendercontext.hpp>

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
        mml::color color;

        BasicMaterial(RenderContext* context);
        void use() const;
    };

    struct StandardMaterial : public Material
    {
        Ref<Texture2D> diffuseMap;

        StandardMaterial(RenderContext* context);
        void use() const;
    };
}