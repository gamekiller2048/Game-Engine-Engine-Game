#include <graphics/camera/orthographic.hpp>
#include <math/transform.hpp>
#include <math/projection.hpp>

namespace mgl
{
    void OrthographicCamera::orthographic(float right, float left, float bottom, float top, float near, float far)
    {
        this->right = right;
        this->left = left;
        this->bottom = bottom;
        this->top = top;
        this->near = near;
        this->far = far;
        
        calculate();
    }

    void OrthographicCamera::calculate()
    {
        view = mml::lookAt(pos, pos + orientation, up);
        projection = mml::orthographic(right, left, bottom, top, near, far);
        projView = projection * view;
    }
}