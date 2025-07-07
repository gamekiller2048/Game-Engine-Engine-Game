#pragma once
#include <graphics/geometry/vertex.hpp>
#include <graphics/render/material.hpp>

namespace VE
{
    enum BlockType
    {
        AIR = 0,
        GRASS = 1,
        DIRT = 2
    };

    inline const BlockType blockTypes[] = {GRASS, DIRT};

    struct BlockVertex
    {
        GLvec3 pos;
        GLvec2 texUV;
        GLvec3 color;
        mgl::VertexLayout vertexLayout() const;
    };

    struct BlockMaterial : public mgl::Material
    {
        BlockMaterial(mgl::RenderContext* context);
        void use() const;
    };
}
