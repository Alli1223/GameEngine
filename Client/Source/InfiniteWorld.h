#pragma once
#include "Chunk.h"
#include "ProceduralTerrain.h"
class InfiniteWorld
{
public:
	//! Constructor
	InfiniteWorld();
	//! Destructor
	~InfiniteWorld();

	std::shared_ptr<Cell> GetCell(float X, float Y);
	std::vector<std::shared_ptr<Cell>> getNeighbourCells(std::shared_ptr<Cell> node);

	//ProceduralTerrain generator;

	//! Creates the infinite world
	void CreateInfiniWorld(GL_Renderer & renderer, b2World* physicsWorld);

	//! Send Chunk
	void OrientateCells(Camera& camera, int x, int y, Cell::GroundType);

	//! Infini World chunks
	std::map<std::pair<int, int>, Chunk> MainLevel;

	int getCellSize() { return cellSize; }
	int getChunkSize() { return chunkSize; }
	int setChunSize(int newSize) { return chunkSize = newSize; }

private:
	int cellSize = 1;
	int chunkSize = 8;
	int levelGenerationRadius = 1;
};