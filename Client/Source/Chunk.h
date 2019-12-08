#pragma once
#include "Cell.h"
#include "GL_Renderer.h"
#include "ProceduralTerrain.h"
class Chunk
{
public:
	//! Consturctor
	Chunk();
	//! Destructor
	~Chunk();

	// Create the chunk from a position
	Chunk::Chunk(b2World* physicsWorld, int initX, int initY);

	json GetJson();
	//! get the chunk size
	int getChunkSize() { return chunkSize; }
	//! TList of lists of cells
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	//! Render the chunk
	void Render(GL_Renderer& renderer);
	void LoadChunk(b2World* physicsWorld, int x, int y);
	//! Get X position of chunk
	int getX() { return x; }
	//! Get Y position of chunk
	int getY() { return y; }

	int getCellSize() { return cellSize; }

	int setPosition(int newX, int newY) { return x = newX, y = newY; }
	ProceduralTerrain generator;
	Timer updateOrientations;
private:
	int x = 0;
	int y = 0;
	int chunkSize = 8;
	glm::ivec2 pos;
	int cellSize = 1;

	std::string savingDirectory = "Resources\\Data\\Chunks\\";
	std::string chunkID;
};

