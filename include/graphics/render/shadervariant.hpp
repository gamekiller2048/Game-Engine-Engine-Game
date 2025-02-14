#pragma once

namespace mgl
{
	enum class RenderPipeline
	{
		FORWARD,
		DEFERRED
	};

	class ShaderVairant
	{
	public:
		std::string srcVert;
		std::string srcFrag;
	};

	class StandardShaderVairant : public ShaderVairant
	{
	public:
		RenderPipeline pipeline;
		bool diffuseMap;
		bool normalMap;
		bool specularMap;
		uint numDirLights;
		uint numPointLights;

		StandardShaderVairant(RenderPipeline pipeline, bool diffuseMap, bool normalMap, bool specularMap, uint numDirLights, uint numPointLights);
	};

	class BasicShaderVairant : public ShaderVairant
	{
	public:
		BasicShaderVairant();
	};
}