#include "mesher.hpp"
#include <math/random.hpp>
#include <intrin.h>
#include "chunk.hpp"

namespace VE
{
    static uint trailingZeros(gInt v)
    {
        unsigned long index;
        if(_BitScanForward(&index, v))
            return index;
        return gSize;
    }

    static uint trailingOnes(gInt v)
    {
        unsigned long index;
        if(_BitScanForward(&index, ~v))
            return index;
        return gSize;
    }

    static gInt checkedShl(gInt v)
    {
        return ((gInt)1 << (v & (gSize - 1))) - (gInt)1 | -(v >= gSize);
    }

    Mesher::Mesher(Chunk* chunk) :
        chunk(chunk) {}

    mgl::Geometry<BlockVertex, GLuint> Mesher::greedyMesh()
    {
        mgl::Geometry<BlockVertex, GLuint> geometry;

        for(int axis = 0; axis < 3; axis++) {
            // each axis that forms a perpendicular plane from the curr axis
            int u; // axis u must be x or z
            int v;
            if(axis == 0) {
                u = 2;
                v = 1;
            }
            else if(axis == 1) {
                u = 0;
                v = 2;
            }
            else {
                u = 0;
                v = 1;
            }

            sweepAxis(DirectionAxes{axis, u, v}, geometry);
        }

        return geometry;
    }

    void Mesher::sweepAxis(const DirectionAxes& dir, mgl::Geometry<BlockVertex, GLuint>& geometry)
    {
        // each slice in that axis
        for(int slice = -1; slice < (int)Chunk::chunkSize[dir.axis]; slice++) {
            auto data = generateMasks(slice, dir);

            for(uint i = 0; i < data.first.size(); i++) {
                greedyMeshFromMask(slice + 1, data.first[i], data.second[i], dir, geometry);
                delete[] data.first[i];
                delete[] data.second[i];
            }
        }
    }

    std::pair<std::vector<gInt*>, std::vector<gInt*>> Mesher::generateMasks(int slice, const DirectionAxes& dir)
    {
        mml::ivec3 pos(0, 0, 0);
        pos[dir.axis] = slice;

        std::vector<gInt*> masks;
        std::vector<gInt*> flips;

        for(const BlockType& blockType : blockTypes) {
            // mask for each block type in a slice
            gInt* mask = new gInt[Chunk::chunkSize[dir.v]]();
            gInt* flip = new gInt[Chunk::chunkSize[dir.v]]();

            // iterate the whole plane
            for(uint pos_v = 0; pos_v < Chunk::chunkSize[dir.v]; pos_v++) {
                for(uint pos_u = 0; pos_u < gSize; pos_u++) {

                    // curr block
                    pos[dir.v] = pos_v;
                    pos[dir.u] = pos_u;
                    BlockType curr = chunk->getVoxel(pos);

                    // the block in front of curr in that axis
                    mml::uvec3 frontPos = pos;
                    frontPos[dir.axis] += 1;
                    BlockType front = chunk->getVoxel(frontPos);

                    // if curr is correct block type and front is air
                    if((curr == blockType && front == AIR) || (curr == AIR && front == blockType))
                        mask[pos_v] |= (gInt)1 << pos_u;

                    if(front == AIR)
                        flip[pos_v] |= (gInt)1 << pos_u;
                }
            }

            masks.push_back(mask);
            flips.push_back(flip);
        }

        return std::make_pair(masks, flips);
    }

    void Mesher::greedyMeshFromMask(int slice, gInt* mask, gInt* flip, const DirectionAxes& dir, mgl::Geometry<BlockVertex, GLuint>& geometry)
    {
        mml::ivec3 pos(0, 0, 0);
        pos[dir.axis] = slice;

        for(uint i = 0; i < Chunk::chunkSize[dir.v]; i++) {
            uint j = 0;
            while(j < gSize) {
                // skip the trailing zeros and add it
                j += trailingZeros(mask[i] >> j);
                
                if(j >= gSize)
                    break;

                // width is the number of trailing ones
                uint w = trailingOnes(mask[i] >> j);

                // binary number containing width number of 1's
                gInt w_as_mask = checkedShl(w);

                // offset bits to j
                gInt wmask = w_as_mask << j;

                uint h = 1;
                while(i + h < Chunk::chunkSize[dir.v]) {
                    // remove all 1's other then those in w_as_mask
                    gInt next_row_h = (mask[i + h] >> j) & w_as_mask;

                    if(next_row_h != w_as_mask or flip[i] >> j != flip[i + h] >> j)
                        break;

                    // erase bits from mask
                    mask[i + h] &= ~wmask;
                    h += 1;
                }
                // erase bits at mask[i]
                mask[i] &= ~wmask;

                // top corner in the u and v axises
                pos[dir.u] = j;
                pos[dir.v] = i;

                // dimensions in the u and v axises
                mml::uvec3 dim_u(0, 0, 0);
                dim_u[dir.u] = w;

                mml::uvec3 dim_v(0, 0, 0);
                dim_v[dir.v] = h;

                
                mml::vec3 uvec(0);
                uvec[dir.u] = 1;
                mml::vec3 vvec(0);
                vvec[dir.v] = 1;

                mml::vec3 color = vvec.cross(uvec);
                
                BlockVertex v0{GLvec3(pos.x, pos.y, pos.z), GLvec2(), color}; // top left
                BlockVertex v1{GLvec3(pos.x + dim_u.x, pos.y + dim_u.y, pos.z + dim_u.z), GLvec2(), color};  // top right
                BlockVertex v2{GLvec3(pos.x + dim_v.x, pos.y + dim_v.y, pos.z + dim_v.z), GLvec2(), color};  // bottom left
                BlockVertex v3{GLvec3(pos.x + dim_u.x + dim_v.x, pos.y + dim_u.y + dim_v.y, pos.z + dim_u.z + dim_v.z), GLvec2(), color}; // bottom right

                int v = geometry.vertices.size();
                if(!flip[i] >> j) {
                    geometry.vertices.push_back(v0);
                    geometry.vertices.push_back(v1);
                    geometry.vertices.push_back(v2);
                    geometry.vertices.push_back(v3);
                }
                else {
                    geometry.vertices.push_back(v3);
                    geometry.vertices.push_back(v2);
                    geometry.vertices.push_back(v1);
                    geometry.vertices.push_back(v0);
                }

                geometry.indices.push_back(v);
                geometry.indices.push_back(v + 1);
                geometry.indices.push_back(v + 2);

                geometry.indices.push_back(v + 1);
                geometry.indices.push_back(v + 2);
                geometry.indices.push_back(v + 3);

                j += w;
            }
        }
    }

}