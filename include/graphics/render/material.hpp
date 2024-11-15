#pragma once
#include <math/math.hpp>
#include <graphics/render/shaderprogram.hpp>
#include <graphics/render/texture2d.hpp>

namespace mgl
{
	struct Material
	{
		Ref<ShaderProgram> shader;
		virtual void use() const = 0;
	};

    struct BasicMaterial : public Material
    {
        mml::vec4 color;

        BasicMaterial();
        void use() const;
    };

    struct StandardMaterial : public Material
    {
        Ref<Texture2D> diffuseMap;
        Ref<Texture2D> normalMap;
        Ref<Texture2D> specularMap;

        StandardMaterial();
        void use() const;
    };
}