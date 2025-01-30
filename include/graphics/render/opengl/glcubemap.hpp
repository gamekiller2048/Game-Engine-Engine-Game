#include <graphics/render/cubemap.hpp>
#include <graphics/render/shaderprogram.hpp>

namespace mgl
{
    class GLCubeMapImpl;
    class GLCubeMap : public CubeMap
    {
    public:
        GLCubeMap(RenderContext* context);
        ~GLCubeMap();

        void bind() const;
        void unbind() const;
        void uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const;
        void loadFromFile(const std::string& filePath) const;
        void allocate(uint width, uint height, TextureFormat format) const;

        GLCubeMapImpl* getImpl() const;

    protected:
        Owned<GLCubeMapImpl> impl;
    };
}