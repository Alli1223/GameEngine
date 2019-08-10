#include "stdafx.h"
#include "InfiniteWorld.h"


InfiniteWorld::InfiniteWorld()
{
	Chunk tempC;
	cellSize = tempC.getCellSize();
	//tempC.~Chunk();
}


InfiniteWorld::~InfiniteWorld()
{
}

void InfiniteWorld::CreateInfiniWorld(GL_Renderer& renderer, b2World* physicsWorld)
{
	
	int numOfChunksWidth = ((renderer.camera.windowSize.x / cellSize) / chunkSize) + levelGenerationRadius;
	int numOfChunksHeight = ((renderer.camera.windowSize.y / cellSize) / chunkSize) + levelGenerationRadius;
	renderer.camera.ChunksOnScreen.x = numOfChunksWidth;
	renderer.camera.ChunksOnScreen.y = numOfChunksHeight;
	int numOfChunksGen = 0;

	for (int i = ((renderer.camera.getX() / cellSize) / chunkSize) - levelGenerationRadius; i < ((renderer.camera.getX() / cellSize) / chunkSize) + numOfChunksWidth; i++)
	{
		for (int j = ((renderer.camera.getY() / cellSize) / chunkSize) - levelGenerationRadius; j < ((renderer.camera.getY() / cellSize) / chunkSize) + numOfChunksHeight; j++)
		{
			if (!MainLevel[{i, j}].tiles.size() > 0)
			{
				Chunk chunk(physicsWorld, i, j);
				chunkSize = chunk.getChunkSize();
				
				numOfChunksGen++;
				MainLevel[{i, j}] = chunk;
			}
		}
	}
	
}
