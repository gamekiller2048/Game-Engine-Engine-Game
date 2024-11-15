#include <graphics/render/pointlight.hpp>
#include <math/transform.hpp>
#include <math/projection.hpp>

namespace mgl
{
    PointLight::PointLight(const mml::vec3& pos, const mml::color& color, float ambient, float a, float b, float specIntensity) :
        Light(LightType::POINT, color, specIntensity), pos(pos), ambient(ambient), a(a), b(b) {}
}
