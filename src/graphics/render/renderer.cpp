#include <graphics/render/renderer.hpp>
#include <graphics/geometry/shape2d.hpp>

namespace mgl
{
    //void Renderer::render(const std::vector<Ref<ModelMesh>>& meshes, const Camera& camera, const Ref<Light>& light, const Ref<Shadow>& shadow)
    //{
    //    shadow->startFrame();
    //    shadow->setProjection(light.get());
    //    for(const Ref<ModelMesh> mesh : meshes) {
    //        shadow->getShader().use();
    //        shadow->getShader().uniformMat4(shadow->getShader().getUniform("u_model"), mesh->getTransform());
    //        mesh->draw(shadow->getShader());
    //    }
    //    shadow->endFrame();

    //    for(const Ref<ModelMesh> mesh : meshes) {
    //        ShaderProgram& shader = mesh->getMaterial()->getShader();

    //        shader.use();
    //        shader.uniformMat4(shader.getUniform("u_projection"), camera.matrix);
    //        shader.uniformMat4(shader.getUniform("u_model"), mesh->getTransform());

    //        light->use(shader);
    //        shader.uniformVec3(shader.getUniform("u_cameraPos"), camera.pos);
    //        //shader.uniformMat4(shader.getUniform("u_lightProjection"), light->getProjection());

    //        
    //        mesh->getMaterial()->use();
    //        shadow->use(shader);
    //        mesh->draw(shader);
    //    }
    //}

    void Renderer::render(RenderScene& scene)
    {
        for(const Ref<Light>& light : scene.getLights()) {
            if(light->shadows) {
                light->shadow->startFrame();
                light->shadow->shader.use();
                light->shadow->use(light);
                for(const Ref<ModelMesh> mesh : scene.getMeshes()) {
                    light->shadow->useMeshTransform(mesh);
                    mesh->draw(light->shadow->shader);
                }
                
                light->shadow->endFrame();
            }
        }

        for(const Ref<ModelMesh> mesh : scene.getMeshes()) {
            const Ref<Material>& material = mesh->getMaterial();
            material->shader.use();
            material->use();

            if(Ref<StandardMaterial> standardMaterial = std::dynamic_pointer_cast<StandardMaterial>(material)) {
                standardMaterial->useCamera(scene.getCamera());
                standardMaterial->useMeshTransform(mesh);

                uint directionalLightIndex = 0;
                uint pointLightIndex = 0;
                for(const Ref<Light>& light : scene.getLights()) {
                    if(light->type == LightType::DIRECTIONAL) {
                        standardMaterial->useDirectionalLight(std::static_pointer_cast<DirectionalLight>(light), directionalLightIndex);
                        directionalLightIndex++;
                    }
                    else if(light->type == LightType::POINT) {
                        standardMaterial->usePointLight(std::static_pointer_cast<PointLight>(light), pointLightIndex);
                        pointLightIndex++;
                    }
                }
            }
            mesh->draw(material->shader);
        }
    }
}
