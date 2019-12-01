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

std::shared_ptr<Cell>& InfiniteWorld::GetCell(float X, float Y)
{
	// Get the chunk
	float chunkSize = getChunkSize();
	int chunkX = (X / chunkSize);
	int chunkY = (Y / chunkSize);
	// Get the cell pos
	int cellX = X - (float)(chunkX * chunkSize);
	int cellY = Y - (float)(chunkY * chunkSize);

	if (cellX > chunkSize)
		cellX = cellX - (chunkX * chunkSize);
	if (cellY > chunkSize)
		cellY = cellY - (chunkY * chunkSize);

	// If the cell is negative then offset the position by chunksize
	if (X < 0.0f)
	{
		cellX += chunkSize - 1;
		chunkX -= 1;

	}
	if (Y < 0.0f)
	{
		cellY += chunkSize - 1;
		chunkY -= 1;
	}

	//std::cout << "Getting Chunk: " << chunkX << ", " << chunkY << " -- Cell: " <<cellX << ", " << cellY << std::endl;

	if (cellX < chunkSize && cellY < chunkSize)
	{
		// If tiles doesnt exist
		if (MainLevel[{ chunkX, chunkY }].tiles.size() == 0)
		{
			std::shared_ptr<Cell> nothing;
			return nothing;
		}
		// Return the tile
		else
		{
			return MainLevel[{ chunkX, chunkY }].tiles[cellX][cellY];

		}
	}

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

void InfiniteWorld::OrientateCells(Camera& camera, int x, int y)
{
	for (int cX = -1; cX < MainLevel[{x, y}].getChunkSize(); cX++)
	{
		for (int cY = -1; cY < MainLevel[{x, y}].getChunkSize(); cY++)
		{
			if (cX == -1 || cY == -1 || cX == getChunkSize() || cY == getChunkSize())
			{
				generator.populateTerrain(MainLevel[{x, y}].tiles);
			}
			GetCell(x, y);
		}
	}

	generator.populateTerrain(MainLevel[{x, y}].tiles);
}
