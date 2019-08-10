#pragma once
#include "Level.h"
#include "Camera.h"
#include "Character.h"
#include "player.h"
#include "GameSettings.h"
#include "Light.h"
#include "GameObject.h"
#include "World.h"
class Rendering
{
public:
	Rendering();
	~Rendering();
	//! Render all game objects
	void RenderObjects(World& world, GL_Renderer& renderer, Player& player, GameSettings& gameSettings);
	//! Renders the level
	void RenderLevel(Level& level, GameSettings& gameSettings, Player& player, GL_Renderer& renderer);
	//! Renders a building
	void RenderBuilding(std::shared_ptr<Building>& building, GameSettings& gameSettings, Player& player, SDL_Renderer* renderer);
	//! Render player
	void RenderPlayer(SDL_Renderer* renderer, Player& player, Level& level);
	//! render cells around objects
	void renderCellsAroundObject(Level& level, int& x, int& y);
	void AssignTileSprites(std::vector<std::vector<std::shared_ptr<Cell>>>& tiles, int x, int y);
	//! Render player stats
	bool renderStats = false;
	//! If the game has darkness
	bool isThereDarkness = true;
	
private:

	//Target Darkness
	float Tdarkness;
	float darkness = 255;
	float time = 0;

	const std::string SpriteSheets = "Resources\\Sprites\\SpriteSheets\\";
	const std::string RoomSpriteTextureLocation = "Resources\\Sprites\\roomSprites\\texturePack\\";
	const std::string ItemsSpriteTextureLocation = "Resources\\Sprites\\SpawnItems\\";
	const std::string TerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\";
	const std::string TreeTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\Trees\\";
	const std::string WallSpriteTextureLocation = "Resources\\Sprites\\Terrain\\Walls\\";
	const std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	const std::string playerStatsTextureLocation = "Resources\\Sprites\\GUI\\PlayerStats\\";

	const std::string rogueLikeAtlasTextureLocation = "Resources\\Sprites\\SpriteSheets\\";

	//! Summer Sprite Locations
	const std::string summerTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\SUMMER\\";
	const std::string springTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\SPRING\\";
	const std::string autumnTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\AUTUMN\\";
	const std::string winterTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\WINTER\\";
	// Textures for game objects

	//! Are the textures for the statusbars


	//TODO: load json file containing the array of different texture IDs //56 cells long
	int grassID = 5;
	int dirtID = 6;
	int sandID = 8;
	int waterID = 0;
	int water2ID = 1;
	int rockID = 614;
	int stoneID = 177;
	int redFlower = 542;
	int whiteFlower = 573;
	int blueFlower = 541;
	int redBerryBush = 528;
	int longGrass1 = 638;
	int longWood = 179;

	int woodFence = 1358;
	int woodHalfFence = 1415;

	int treeTop = 583;
	int treeBottom = 640;

	int waterTopLeft = 2;
	int waterTopMiddle = 3;
	int waterTopRight = 4;

	int waterMiddleLeft = 59;
	int waterMiddle = 60;
	int waterMiddleRight = 61;


	int waterBottomLeft = 116;
	int waterBottomMiddle = 117;
	int waterBottomRight = 118;

	
	
	enum layers
	{
		seaLevel,
		ground,
		onGround,
		isCrops,
		abovePlayer
	};
	
};
