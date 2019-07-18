#pragma once
#include "Chunk.h"
#include "Instance.h"
class InfiniteWorld : public Instance
{
public:
	InfiniteWorld();
	~InfiniteWorld();

	void CreateInfiniWorld(GL_Renderer & renderer);

	//! Gets a cell from the infinite world
	std::shared_ptr<Cell>& GetCell(float x, float y);

	//! Infini World
	std::map<std::pair<int, int>, Chunk> MainLevel;
	int getCellSize() { return cellSize; }
	int getChunkSize() { return chunkSize; }
	int setChunSize(int newSize) { return chunkSize = newSize; }

private:
	int cellSize = 100;
	int chunkSize = 8;
	int levelGenerationRadius = 1;
};

