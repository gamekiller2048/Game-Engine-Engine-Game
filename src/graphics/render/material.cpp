#include <graphics/render/material.hpp>

namespace mgl
{
	Material::Material(RenderContext* context) :
		context(context) {}

	BasicMaterial::BasicMaterial(RenderContext* context, const BasicShaderVairant& shaderVariant) :
		Material(context)
	{
		shader = context->createShaderProgram();
		shader->attachGLSLShadersFromSrc(shaderVariant.srcVert, shaderVariant.srcFrag);
	}

	void BasicMaterial::use() const
	{
		shader->uniform("u_albedo", (mml::vec4)albedo);
	}

	StandardMaterial::StandardMaterial(RenderContext* context, const StandardShaderVairant& shaderVariant) :
		Material(context), shaderVariant(shaderVariant)
	{
		shader = context->createShaderProgram();
		shader->attachGLSLShadersFromSrc(shaderVariant.srcVert, shaderVariant.srcFrag);
	}

	void StandardMaterial::use() const
	{
		if(shaderVariant.diffuseMap) {
			diffuseMap->bindUnit();
			diffuseMap->uniformSampler(shader, "u_diffuseMap");
		}
		else
			shader->uniform("u_albedo", (mml::vec4)albedo);

		if(shaderVariant.normalMap) {
			normalMap->bindUnit();
			normalMap->uniformSampler(shader, "u_normalMap");
		}
		if(shaderVariant.specularMap) {
			specularMap->bindUnit();
			specularMap->uniformSampler(shader, "u_specularMap");
		}
	}
}