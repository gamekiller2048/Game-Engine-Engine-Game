#pragma once
#include "voxel.hpp"
#include "mesher.hpp"

namespace VE
{
	class Chunk
	{
	public:
		void generate();
		
		static BlockType getGlobalVoxel(const mml::ivec3& pos);
		BlockType getVoxel(const mml::ivec3& pos);

		// Note: chunkSize.x and chunkSize.z must be gSize
		static inline constexpr mml::uvec3 chunkSize = mml::uvec3(gSize, 64, gSize);

	protected:
		// worldPos of the top-right block
		mml::ivec3 chunkPos;
		BlockType* grid;
	};

}