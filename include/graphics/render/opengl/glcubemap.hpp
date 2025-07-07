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

        void bindUnit() const;
        void unbind() const;
        void uniformSampler(const Ref<ShaderProgram>& shader, const std::string& loc) const;
        void loadFromFile(const std::array<std::string, 6>& filePaths) const;
        void allocate(uint width, uint height, TextureFormat format, TextureFormat internalFormat) const;

        GLCubeMapImpl* getImpl() const;

    protected:
        Owned<GLCubeMapImpl> impl;
    };
}