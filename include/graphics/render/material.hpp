#pragma once
#include <math/math.hpp>
#include <graphics/opengl/shaderprogram.hpp>
#include <graphics/opengl/texture2d.hpp>
#include <graphics/core/resource.hpp>
#include <graphics/render/pointlight.hpp>
#include <graphics/render/directionallight.hpp>
#include <graphics/camera/camera.hpp>

namespace mgl
{
    class Renderer;
    class ModelMesh;

    struct Material
    {
        ShaderProgram shader;
        virtual void use() const = 0;
    };

    class BasicMaterial : public Material
    {
    public:
        mml::vec4 color;

        BasicMaterial(const mml::color& color);
        
        void create();
        void use() const;
    };

    class StandardMaterial : public Material
    {
    public:
        Ref<Texture2D> diffuseMap;
        Ref<Texture2D> normalMap;
        Ref<Texture2D> specularMap;

        StandardMaterial() = default;
        StandardMaterial(const Ref<Texture2D>& diffuseMap, const Ref<Texture2D>& normalMap, const Ref<Texture2D>& specularMap);

        void create();
        void use() const;
        void usePointLight(const Ref<PointLight>& light, uint index) const;
        void useDirectionalLight(const Ref<DirectionalLight>& light, uint index) const;
        void useCamera(const Ref<Camera>& camera);
        void useMeshTransform(const Ref<ModelMesh>& mesh);
    };

    class Basic2DTextureMaterial : public Material
    {
    public:
        Ref<Texture2D> texture;

        Basic2DTextureMaterial(const Ref<Texture2D>& texture);

        void create();
        void use() const;
    };
}
