#pragma once

namespace mgl
{
	enum class RenderApi {
		OPENGL
	};

	class Mesh;
	class VertexBuffer;
	class IndexBuffer;
	class ShaderProgram;
	class Texture2D;
	class CubeMap;

	class Window;
	class RenderContext
	{
	public:
		RenderContext() = default;
		virtual ~RenderContext() = default;

		Ref<Mesh> createMesh();

		virtual Ref<VertexBuffer> createVertexBuffer() = 0;
		virtual Ref<IndexBuffer> createIndexBuffer() = 0;
		virtual Ref<ShaderProgram> createShaderProgram() = 0;
		virtual Ref<Texture2D> createTexture2D() = 0;
		virtual Ref<CubeMap> createCubeMap() = 0;

		virtual void useWindow(const Ref<Window>& window) = 0;
		virtual void makeCurrent() = 0;
		virtual void swapBuffers() = 0;
		virtual bool isCurrent() const = 0;
		virtual bool isWindowUsed(const Ref<Window>& window) const = 0;

		virtual void clearColor() const = 0;
		virtual void clearDepth() const = 0;
	};
}