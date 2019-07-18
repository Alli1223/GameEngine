#include "stdafx.h"
#include "Atlas.h"


Atlas::Atlas()
{
}

Atlas::Atlas(std::string newAtlasFileLocation, int newAtlasTileWidth, int newAtlasTileSize)
{
	spritesInWitdth = newAtlasTileWidth;
	atlasTileSize = newAtlasTileSize;
	atlasFileLocation = newAtlasFileLocation;
}


Atlas::~Atlas()
{
}
