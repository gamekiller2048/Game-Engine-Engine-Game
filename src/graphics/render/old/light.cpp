#include <graphics/render/light.hpp>

namespace mgl
{
    Light::Light(LightType type, const mml::color& color, float specIntensity) :
        type(type), color(color), specIntensity(specIntensity) {}
}
