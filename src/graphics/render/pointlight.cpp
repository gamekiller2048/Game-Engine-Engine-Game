#include <graphics/render/pointlight.hpp>
#include <math/transform.hpp>
#include <math/projection.hpp>

namespace mgl
{
    PointLight::PointLight(const mml::vec3& pos, const mml::color& color, float ambient, float a, float b, float intensity, float specIntensity) :
        Light(LightType::POINT, color, intensity, specIntensity), pos(pos), ambient(ambient), a(a), b(b) {}

    void PointLight::use(const Ref<ShaderProgram>& shader, uint index) const
    {
        const std::string base = "u_pointLights[" + std::to_string(index) + "].";
        shader->uniform(base + "pos", pos);
        shader->uniform(base + "color", (mml::vec4)color);
        shader->uniform(base + "ambient", ambient);
        shader->uniform(base + "a", a);
        shader->uniform(base + "b", b);
        shader->uniform(base + "intensity", intensity);
        shader->uniform(base + "specIntensity", specIntensity);

        if(shadow) {
            shader->uniform(base + "shadow.farPlane", shadow->farPlane);

            shadow->getCubeMap()->bindUnit();
            shadow->getCubeMap()->uniformSampler(shader, base + "shadow.cubemap");
        }
    }

    void PointLight::createShadow(RenderContext* context, const mml::uvec2& size)
    {
        shadow = CreateRef<PointShadow>(context);
        shadow->create(size);
    }

    void PointLight::useShadow() const
    {
        mml::mat4 shadowProj = shadow->getCamera()->projection;
        std::vector<mml::mat4> shadowTransforms = {
            shadowProj * mml::lookAt(pos, pos + mml::RIGHT, mml::DOWN),
            shadowProj * mml::lookAt(pos, pos + mml::LEFT, mml::DOWN),
            shadowProj * mml::lookAt(pos, pos + mml::UP, mml::FORWARD),
            shadowProj * mml::lookAt(pos, pos + mml::DOWN, mml::BACKWARD),
            shadowProj * mml::lookAt(pos, pos + mml::FORWARD, mml::DOWN),
            shadowProj * mml::lookAt(pos, pos + mml::BACKWARD, mml::DOWN)
        };

        shadow->getShader()->uniforms("u_shadowMats", shadowTransforms);
        shadow->getShader()->uniform("u_lightPos", pos);
        shadow->getShader()->uniform("u_farPlane", std::static_pointer_cast<PointShadow>(shadow)->farPlane);
    }

    Ref<Shadow> PointLight::getShadow() const
    {
        return shadow;
    }
}
