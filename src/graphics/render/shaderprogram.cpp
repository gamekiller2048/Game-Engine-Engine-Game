#include <graphics/render/shaderprogram.hpp>
#include <graphics/app.hpp>
#include <graphics/render/opengl/shaderprogram.hpp>

namespace mgl
{
	Ref<ShaderProgram> createShaderProgram()
	{
		switch(App::getInstance()->getRenderApi()) {
		case RenderApi::OPENGL:
			return CreateRef<gl::ShaderProgram>();
		}

		return nullptr;
	}
}