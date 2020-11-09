#pragma once
#include "Instance.h"
#include "ProceduralTerrain.h"
class InfiniteWorld
{
public:
	//! Constructor
	InfiniteWorld();
	//! Destructor
	~InfiniteWorld();

	//! Get a cell from the map of cells
	std::shared_ptr<Cell> GetCell(float X, float Y);

	//ProceduralTerrain generator;

	//! Orientate a cell based on surrounding cell types
	void OrientateCell(std::shared_ptr<Cell> node);

	//! Infini World chunks
	std::map<std::pair<int, int>, std::shared_ptr<Cell>> Level;

private:

};