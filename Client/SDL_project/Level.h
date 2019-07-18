#pragma once
#include "Cell.h"
#include "Chunk.h"
#include "Point.h"
#include "Camera.h"
#include "ProceduralTerrain.h"
#include "Building.h"
#include "PlayerShop.h"

//! This class generates the base of the level 
/*!
This class creates a vector of vector of shared pointers to cells
*/

class Level
{
public:
	//! A constructor
	Level();
	//! A deconstructor 
	~Level();

	void Level::CreateLevel(int x, int y);
	void CreateLevelFromJson(json level);
	//! The base grid that contains the cells
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	int getCellSize() { return cellSize; }
	int setCellSize(int newCellSize) { return cellSize = newCellSize; }
	int setCellsInWindowSize(int xVal, int yVal) { return cellsInWindowWidth = xVal, cellsInWindowHeight = yVal; }
	int cellsInWindowWidth = 0, cellsInWindowHeight = 0;
protected:
	
	int levelWidth, levelHeight;
	int cellSize;
	int defaultLevelSize = 100;
};