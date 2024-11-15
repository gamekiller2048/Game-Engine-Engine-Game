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
			void main()
			{
				gl_Position = vec4(pos, 1) * projection;
			})",

			R"(
			#version 430 core
			void main()
			{
				gl_FragColor = vec4(1);
			})"
		);
	}
	void BasicMaterial::use() const
	{
		
	}

	StandardMaterial::StandardMaterial()
	{

	}

	void StandardMaterial::use() const
	{

	}
}