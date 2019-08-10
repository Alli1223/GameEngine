#include "stdafx.h"
#include "Chunk.h"

// Check if a file exists
inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

Chunk::Chunk()
{
	Cell cell;
	cellSize = cell.getCellSize();
	tiles.reserve(chunkSize);
}

// Generate a chunk
Chunk::Chunk(b2World* physicsWorld, int initX, int initY)
{
	x = initX;
	y = initY;
	pos = { x,y };
	chunkID = "X:" + std::to_string(x) + ",Y:" + std::to_string(y);

	// Create the tiles
	for (int x = 0; x < chunkSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;

		tiles.push_back(column);
		for (int y = 0; y < chunkSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(physicsWorld, x + (initX * chunkSize), y + (initY * chunkSize), "Autumn_Ground_29");
			cell.tilePos.x = x;
			cell.tilePos.y = y;
			cell.isWalkable = true;
			
			//cell.InitPhysics(physicsWorld, b2BodyType::b2_dynamicBody);
			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[x].push_back(sharedCell);
		}
	}

	// Load the chunk from file if it exists
	std::string location = savingDirectory + std::to_string(x) + "_" + std::to_string(y) + ".json";
	if (exists(location))
		LoadChunk(physicsWorld, initX, initY);
	else
	{
		generator.populateTerrain(tiles);
	}
}

void Chunk::Render(GL_Renderer& renderer)
{
	for (int x = 0; x < tiles.size(); x++)
		for (int y = 0; y < tiles[x].size(); y++)
		{
			cellSize = tiles[0][0]->getCellSize();

			tiles[x][y]->Render(renderer);
			//renderer.RenderText(std::to_string(x) + ", " + std::to_string(y), tiles[x][y]->getPosition() - renderer.camera.getPosition(), { 50.0f, 50.0f }, { 0.2f, 0.2f }, { 100,100,100 });
		}
}

void Chunk::LoadChunk(b2World* physicsWorld, int x, int y)
{
	std::string location = savingDirectory + std::to_string(x) + "_" + std::to_string(y) + ".json";
	if (exists(location))
	{
		std::ifstream t(location);
		std::string jsonData((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		json data = json::parse(jsonData.begin(), jsonData.end());
		json tileData = data.at("Tiles");

		// Other chunk data
		//chunkSize = data.at("ChunkSize");
		//ivec2 pos = data.at("Pos");
		//setPosition(pos.x, pos.y);
		for (auto& tile : tileData)
		{
			Cell newCell(physicsWorld, tile);

			int tileX = newCell.tilePos.x;
			int tileY = newCell.tilePos.y;

			//newCell.InitPhysics(physicsWorld, b2BodyType::b2_staticBody);
			// Set the cell
			this->tiles[tileX][tileY] = std::make_shared<Cell>(newCell);
		}
	}
}

Chunk::~Chunk()
{
	if(!tiles.empty())
		tiles.erase(tiles.begin() , tiles.end());

}
