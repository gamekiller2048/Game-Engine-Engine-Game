#include <graphics/render/cubemap.hpp>

namespace mgl
{
    class GLCubeMapImpl;
    class GLCubeMap : public CubeMap
    {
    public:
        GLCubeMap(RenderContext* context);
        ~GLCubeMap();

        void bind();
        void unbind();

        GLCubeMapImpl* getImpl() const;

    protected:
        Owned<GLCubeMapImpl> impl;
    };
}