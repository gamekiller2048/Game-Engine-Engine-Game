#pragma once
#include <graphics/render/rendercontext.hpp>

namespace mgl
{
	class CubeMap
	{
	public:
		CubeMap(RenderContext* context);

	protected:
		RenderContext* context;
	};
}