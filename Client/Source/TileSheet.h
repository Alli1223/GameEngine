#pragma once
#include "Texture2D.h"
#include "Atlas.h"
class TileSheet : public Atlas
{
public:
	TileSheet();
	~TileSheet();

	uint startingGID = 0;
	uint columns = 0;
	std::string imageLocation;
	std::string name;
	uint imageheight;
	uint imagewidth;
	uint margin;
	uint spacing;
	uint tilecount;
	uint tileheight;
	uint tilewidth;
};

