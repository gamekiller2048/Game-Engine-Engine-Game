#pragma once
#include <math/math.hpp>
#include <vector>
#include <tuple>
#include "voxel.hpp"

namespace VE
{
    typedef uint gInt;
    static constexpr uint gSize = sizeof(gInt) * 8;
    
    struct DirectionAxes
    {
        int axis;
        int u;
        int v;
    };

    class Chunk;
    class Mesher
    {
    public:
        Mesher(Chunk* chunk);
        mgl::Geometry<BlockVertex, GLuint> greedyMesh();
        void sweepAxis(const DirectionAxes& dir, mgl::Geometry<BlockVertex, GLuint>& geometry);
        std::pair<std::vector<gInt*>, std::vector<gInt*>> generateMasks(int slice, const DirectionAxes& dir);
        void greedyMeshFromMask(int slice, gInt* mask, gInt* flip, const DirectionAxes& dir, mgl::Geometry<BlockVertex, GLuint>& geometry);
    
    protected:
        Chunk* chunk;
    };
}