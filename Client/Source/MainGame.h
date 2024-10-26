#pragma once
#include "Texture.h"
#include "Level.h"
#include "Point.h"
#include "Cell.h"
#include "PathFinder.h"
#include "GameSettings.h"
#include "GUI.h"
#include "ToolBar.h"
#include "Item.h"
#include "Rendering.h"
#include "PerlinNoise.h"
#include "ProceduralTerrain.h"
#include "Camera.h"
#include "Inventory.h"
#include "UserInput.h"
#include "player.h"
#include "TextUI.h"
#include "Menu.h"
#include "InventoryUI.h"
#include "CraftingUI.h"
#include "GameUI.h"
#include "PlayerShop.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "GL_Renderer.h"
#include "GameObject.h"
#include "LightSource.h"
#include "LevelSaving.h"
#include "World.h"
#include "Tool.h"
#include "FishingRod.h"
#include "Bug.h"
#include "NetworkManager.h"
#include "Instance.h"
#include "CollisionListener.h"
#include "NetworkInstance.h"
//! The main class
/*!
This is the main class where the game is laoded and run. 
*/

class MainGame
{
public:
	//! A constructor
	MainGame();
	//! A deconstructor
	~MainGame();

	//! Main Run loop
	void run();

	//! Initalising all classes needed for game
	Rendering rendering;
	Level level;
	GameSettings gameSettings;
	Cell cell;
	ProceduralTerrain terrainGen;
	UserInput input;
	GameUI UI;
	World world;
	NetworkInstance s_world;
	Room Shop;
	Pathfinder pathfinder;
	NetworkManager networkManager;
	CollisionListener myListender;
	Timer tickRate;


	static std::shared_ptr<Instance> currentInstance;
	
	//The music that will be played
	Mix_Music *gMusic = NULL;
	bool needsRestart = false;

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;

	//! Coordinates of the mouse 
	int mouseX, mouseY;

	glm::vec2 mouseCellPosition;
private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Pointer to the window that the game will be rendered in
	SDL_Window* window;
	//" Pointer to the renderer
	SDL_Renderer* renderer;

	SDL_GLContext glContext;

	std::vector<std::shared_ptr<Player>> allPlayers;
	

	//! Some colours for text output
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	//! Tick rate of game physics simulation
	float tickrate = 20;

	
};

