#pragma once
#include "player.h"
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
	//! Constructors
	Building();
	Building(b2World* physicsWorld);
	Building(b2World* physicsWorld, json building);
	Building(json building);
	//! Destructor
	~Building();

	void InitBuilding(b2World* physicsWorld);

	virtual void OnEnter();

	virtual void OnExit();

	// Trigger points
	BuildingExit exit;
	BuildingEntrance entrance;
	SpawnLocation spawn;

	std::string BuildingType;

	// Player
	//std::shared_ptr<Player> player = nullptr;

	//! 
	//void BuildingUpdate(GL_Renderer& renderer, UserInput& userInput, GameSettings& gameSettings, GameUI& UI);


	//! Render interior
	void RenderInterior(GL_Renderer& renderer);


	int constructionLevel = 0;

protected:

	std::string modularHouseDirectory = "Resources\\Sprites\\Buildings\\Templates\\";

	
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

