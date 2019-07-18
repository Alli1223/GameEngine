#include "stdafx.h"
#include "InfiniteWorld.h"


InfiniteWorld::InfiniteWorld()
{
	
}


InfiniteWorld::~InfiniteWorld()
{
}

void InfiniteWorld::CreateInfiniWorld(GL_Renderer& renderer)
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
				Chunk chunk(I_Physics.get(), i, j);
				chunkSize = chunk.getChunkSize();
				numOfChunksGen++;
				MainLevel[{i, j}] = chunk;
			}
		}
	}
}

// Convert world pos into chunk vector value 
std::shared_ptr<Cell>& InfiniteWorld::GetCell(float X, float Y)
{
	// Get the chunk
	int chunkSize = getChunkSize();
	int chunkX = (X / chunkSize);
	int chunkY = (Y / chunkSize);
	// Get the cell pos
	int cellX = X - chunkX * chunkSize;
	int cellY = Y - chunkY * chunkSize;

	if (cellX > chunkSize)
		cellX = cellX - (chunkX * chunkSize);
	if (cellY > chunkSize)
		cellY = cellY - (chunkY * chunkSize);

	//if (cellX == -1)
	//{
	//	cellX = 7; // chunksize
	//	chunkX = -1;
	//}
	//if (cellY == -1)
	//{
	//	cellX = chunkSize - 1;
	//	chunkY = -1;
	//}

	//if (cellX < 0)
	//	cellX--;
	//if (cellY < 0)
	//	cellY--;

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
			Chunk chunk(I_Physics.get(), chunkX, chunkY);
			MainLevel[{chunkX, chunkY}] = chunk;
			return MainLevel[{ chunkX, chunkY }].tiles[cellX][cellY];
		}
		// Return the tile
		else
			return MainLevel[{ chunkX, chunkY }].tiles[cellX][cellY];
	}
}