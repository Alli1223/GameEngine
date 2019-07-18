#include "stdafx.h"
#include "Level.h"

Level::Level()
{
	Cell temp;
	setCellSize(temp.getCellSize());
}

Level::~Level()
{
}


// Creates a grid of cells at a specified location
void Level::CreateLevel(int x, int y)
{
	for (int x = 0; x < defaultLevelSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < defaultLevelSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x, y, 0, "Grass");
			
			cell.setSize(cellSize, cellSize);
			cell.isWalkable = true;
			cell.isGrass = true;

			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}
}


void Level::CreateLevelFromJson(json level)
{
	CreateLevel(0, 0);

	int width = level.at("Width").get<int>();
	int height = level.at("Height").get<int>();
	json levelData = level.at("Level");
	int cellSize = level.at("CellSize").get<int>();

	// Get the tiles from file and assign them
	for (auto& tile : levelData)
	{
		Cell newCell(tile);
		newCell.setSize(cellSize, cellSize);
		this->tiles[newCell.getX()][newCell.getY()] = std::make_shared<Cell>(newCell);
	}

}
