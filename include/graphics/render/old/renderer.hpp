#pragma once
#include <vector>
#include <graphics/render/modelmesh.hpp>
#include <graphics/camera/camera.hpp>
#include <graphics/opengl/shader.hpp>
#include <graphics/render/light.hpp>
#include <graphics/render/shadow.hpp>
#include <graphics/opengl/enums.hpp>
#include <graphics/core/resource.hpp>
#include <graphics/render/renderscene.hpp>

namespace mgl
{
    class Renderer
    {
    public:
        //void render(const std::vector<Ref<ModelMesh>>& meshes, const Camera& camera, const Ref<Light>& light, const Ref<Shadow>& shadow)
        void render(RenderScene& scene);
    };
}
