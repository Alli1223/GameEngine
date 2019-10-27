#pragma once
#include "Instance.h"
#include "Cell.h"
#include "RoomDesigner.h"
class Room : public Instance
{
public:
	//! Constructor
	Room();
	//! Deconstructor
	~Room();

	//! Setup room override
	void InstanceSetup(Player& player);

	virtual void Render(GL_Renderer& renderer);
	
	//! room tiles
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	int getRoomSize() { return roomSize; }

	//! Get the tile size in the building
	int getTileSize() { return tileSize; }
	int setTileSize(int newSize) { return tileSize = newSize; }
private:


	int roomSize = 20;
	int tileSize = 50;
	
};

