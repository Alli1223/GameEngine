#pragma once
class Atlas
{
public:
	Atlas();
	Atlas(std::string atlasFileLocation,int atlasTileWidth, int atlasTileSize);
	~Atlas();

	//! How many sprites are in the width of the image
	int spritesInWitdth = 56;
	//! The size of each sprite in pixels
	int atlasTileSize = 16;
	int spritesWdith = 0;
	int spritesHeight = 0;

	//! files location
	std::string atlasFileLocation;
	//! optional normal maps location
	std::string optionalNormalMapLocation;

};


