#pragma once
#include "Chunk.h"
#include "ProceduralTerrain.h"
class InfiniteWorld
{
public:
	InfiniteWorld();
	~InfiniteWorld();

	void CreateInfiniWorld(GL_Renderer & renderer, b2World* physicsWorld);

	//! Infini World
	std::map<std::pair<int, int>, Chunk> MainLevel;
	int getCellSize() { return cellSize; }
	int getChunkSize() { return chunkSize; }
	int setChunSize(int newSize) { return chunkSize = newSize; }

private:
	int cellSize = 1;
	int chunkSize = 8;
	int levelGenerationRadius = 1;
};

