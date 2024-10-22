#include <graphics/render/directionallight.hpp>
#include <math/transform.hpp>
#include <math/projection.hpp>

namespace mgl
{
    DirectionalLight::DirectionalLight(const mml::vec3& dir, const mml::color& color, float ambient, float specIntensity) :
        Light(LightType::DIRECTIONAL, color, specIntensity), dir(dir), ambient(ambient) {}

    mml::mat4 DirectionalLight::getSpaceTransform()
    {
        mml::mat4 projection = mml::orthographic(10.0f, -10.0f, 10.0f, -10.0f, 75.0f, 0.1f);
        mml::mat4 view = mml::lookAt(mml::normalize(dir) * 5, mml::vec3(0), mml::vec3(0.0f, 1.0f, 0.0f));
        return projection * view;
    }
}
