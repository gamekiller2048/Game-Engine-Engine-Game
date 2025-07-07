#pragma once
#include <vector>

namespace mgl
{
    struct VertexLayoutAttribute
    {
        uint layout;
        uint components;
        uint type;
        size_t size;
    };

    struct VertexLayout
    {
        std::vector<VertexLayoutAttribute> attributes;
        size_t size;
    };
}