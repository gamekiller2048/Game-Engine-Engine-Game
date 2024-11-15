#include <graphics/camera/perspective.hpp>
#include <math/projection.hpp>

namespace mgl
{
    void PerspectiveCamera::perspective(float fov, float near, float far, const mml::uvec2& size)
    {
        this->fov = fov;
        this->near = near;
        this->far = far;
        this->size = size;

        calculate();
    }

    void PerspectiveCamera::calculate()
    {
        view = mml::lookAt(pos, pos + orientation, up);
        projection = mml::perspective(mml::radians(fov), far, near, (float)size.x / size.y);
        projView = projection * view;
    }
}