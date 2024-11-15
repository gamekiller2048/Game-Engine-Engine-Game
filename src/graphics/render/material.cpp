#include <graphics/render/material.hpp>

namespace mgl
{
	BasicMaterial::BasicMaterial()
	{
		shader = mgl::createShaderProgram();
		shader->create();
		shader->attachGLSLShadersFromSrc(
			R"(
			#version 430 core
			layout(location = 0) in vec3 pos;
			uniform mat4 projection;
			uniform mat4 transform;
			void main()
			{
				gl_Position = vec4(pos, 1) * transform * projection;
			})",

			R"(
			#version 430 core
			uniform vec4 color;
			void main()
			{
				gl_FragColor = color;
			})"
		);
	}

	void BasicMaterial::use() const
	{
		shader->uniform("color", (mml::vec4)color);
	}

	StandardMaterial::StandardMaterial()
	{

	}

	void StandardMaterial::use() const
	{

	}
}