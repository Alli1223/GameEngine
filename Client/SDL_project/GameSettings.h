#pragma once
#include "Player.h"
#include "Timer.h"
#include "PlayerShop.h"
#include "TileSheet.h"
#include "LevelSaving.h"
class GameSettings
{
public:
	GameSettings();
	~GameSettings();


	//! initial window settings
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;

	//! Save the players settings
	void savePlayerSettings(Player& player);
	Player getPlayerFromSave();
	//! Save the level
	//Level loadGameFromSave(std::string file);
	

	//! Whether the game will save the game when it closes
	bool saveLevelOnExit = false;
	bool savePlayerOnExit = false;

	bool restartGame = false;
	//! Get screen resolution
	void getScreenResolution();
	//! Calculate FPS
	void CalculateFramesPerSecond();

	//Timer used to update the caption
	Timer fpsTimer;
	float getAverageFPS() { return avgFPS; }
	static const bool displayFPS = false;


	Uint32 elapsedTime = 0;
	Uint32 lastFrameTimeElapsed = 0;
	float deltaTime = 0;

	//! Whether the game is fullscreen
	bool fullscreen = false;
	bool displayMouse = false;
	int mousePointerSize = 25;

	//! Main Menu toggle
	bool mainMenu = false;
	bool inGameMenu = false;

	bool gotoMainMenu = false;
	//! The cell the mouse is hovering over
	glm::vec2 mouseCellPos;

	//! Whether the game uses networking and false if singleplayer
	bool useNetworking = true;


	//! Whether the game is running or not
	bool running = true;
	//! stores screen resolution
	SDL_DisplayMode currentDisplay;

	//! Level saving class
	LevelSaving levelSaving;
	
private:
	TileSheet getTileSetFromID(int ID);
	std::vector<TileSheet> Tiled_TileSheets;
	std::ofstream playerSave;
	std::ofstream levelSave;

	std::string levelSavePath = "Resources\\Data\\levelData.txt";
	std::string map1 = "Resources\\Data\\test.json";
	std::string playerSavePath = "Resources\\Data\\playerData.txt";

	//The frames per second timer
	//Timer used to calculate the frames per second
	int frame = 0;
	//Start counting frames per second
	int countedFrames = 0;
	float avgFPS = 0;

};

