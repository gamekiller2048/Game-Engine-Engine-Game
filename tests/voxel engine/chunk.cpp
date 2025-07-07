#include "chunk.hpp"
#include "FastNoiseLite.h"

namespace VE
{

	BlockType Chunk::getGlobalVoxel(const mml::ivec3& pos)
	{
		return (BlockType)0;
	}

	BlockType Chunk::getVoxel(const mml::ivec3& pos)
	{
		if(!(pos.x >= 0 && pos.x < gSize && pos.y >= 0 && pos.y < chunkSize.y && pos.z >= 0 && pos.z < gSize))
			return AIR;
		return grid[pos.x + pos.z * gSize + pos.y * (gSize * gSize)];
	}

	void Chunk::generate()
	{
		FastNoiseLite noise;
		noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

		grid = new BlockType[chunkSize.x * chunkSize.y * chunkSize.z]();
		for(int x = 0; x < gSize; x++) {
			for(int z = 0; z < gSize; z++) {
				int n = (int)(noise.GetNoise((float)x, (float)z) * 100);
				for(int y = chunkSize.y / 2 + n; y >= 0; y--)
					grid[(x + z * gSize + y * gSize * gSize)] = DIRT;
			}
		}
	}
}