#pragma once
#include "Player.h"
#include "Cell.h"


struct BuildingExit : public GameObject
{
public:

};

struct BuildingEntrance : public GameObject
{
public:

};

struct SpawnLocation : public GameObject
{
public:
	glm::vec2 previousLocation;
};


class Building : public GameObject
{
public:
	//! Constructor
	Building();
	Building(json building);

	//! Destructor
	~Building();

	void InitBuilding();

	void OnEnter();

	void OnExit();

	// Trigger points
	BuildingExit exit;
	BuildingEntrance entrance;
	SpawnLocation spawn;

	std::string BuildingType;

	//! Tiles
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	// Player
	//std::shared_ptr<Player> player = nullptr;

	//! 
	//void BuildingUpdate(GL_Renderer& renderer, UserInput& userInput, GameSettings& gameSettings, GameUI& UI);

	//! Get the tile size in the building
	int getTileSize() { return tileSize; }
	int setTileSize(int newSize) { return tileSize = newSize; }

	//! Render interior
	void RenderInterior(GL_Renderer& renderer);
	//! is player inside
	bool playerIsInside = false;

	int getRoomSize() { return roomSize; }

	int constructionLevel = 0;

protected:

	std::string modularHouseDirectory = "Resources\\Sprites\\Buildings\\Templates\\";
	int roomSize = 20;
	int tileSize = 50;
	
	glm::vec2 cellPos;
	glm::vec2 spawnPoint;
	glm::vec2 exitPoint;
	glm::vec2 returnCell;
	glm::vec2 entrancePoint;

	Texture2D GroundFloorBackground;
	Texture2D GroundFloorDecoration;
	Texture2D GroundFloorWindows;
	Texture2D GroundFloorDoor;
	Texture2D FirstFloorBackground;
	Texture2D FirstFloorDecoration;
	Texture2D RoofBackground;
	Texture2D RoofDecoration;

	bool init = false;

	//! Building Physics
	//std::unique_ptr<b2World> physics;
};

