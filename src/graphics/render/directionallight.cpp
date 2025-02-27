#include <graphics/render/directionallight.hpp>
#include <math/transform.hpp>
#include <math/projection.hpp>

namespace mgl
{
    DirectionalLight::DirectionalLight(const mml::vec3& dir, const mml::color& color, float ambient, float intensity, float specIntensity) :
        Light(LightType::DIRECTIONAL, color, intensity, specIntensity), dir(dir), ambient(ambient) {}

    void DirectionalLight::use(const Ref<ShaderProgram>& shader, uint index) const
    {
        const std::string base = "u_directionalLights[" + std::to_string(index) + "].";
        shader->uniform(base + "dir", dir);
        shader->uniform(base + "color", (mml::vec4)color);
        shader->uniform(base + "ambient", ambient);
        shader->uniform(base + "intensity", intensity);
        shader->uniform(base + "specIntensity", specIntensity);

        if(shadow) {
            shader->uniform(base + "projection", getLightProjection());
            shader->uniform(base + "shadows", true);
            shader->uniform(base + "shadow.bias", shadow->bias);
            shader->uniform(base + "shadow.sampleRadius", shadow->sampleRadius);
            
            shadow->getMap()->bindUnit();
            shadow->getMap()->uniformSampler(shader, base + "shadow.map");
        }
    }

    void DirectionalLight::createShadow(RenderContext* context, const mml::uvec2& size)
    {
        shadow = CreateRef<DirectionalShadow>(context);
        shadow->create(size);
    }

    mml::mat4 DirectionalLight::getLightProjection() const
    {
        return shadow->getCamera()->projection * mml::lookAt(mml::normalize(-dir), mml::vec3(0), mml::UP);
    }

    void DirectionalLight::useShadow() const
    {
        shadow->getShader()->uniform("u_lightSpaceTransform", getLightProjection());
    }

    Ref<Shadow> DirectionalLight::getShadow() const
    {
        return shadow;
    }
}
