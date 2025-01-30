#include <graphics/render/light.hpp>

namespace mgl
{
    Light::Light(LightType type, const mml::color& color, float intensity, float specIntensity) :
        type(type), color(color), intensity(intensity), specIntensity(specIntensity) {}
}
