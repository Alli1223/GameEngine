#pragma once
#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "GameWindow.h"
#include "Cell.h"
#include "World.h"
#include "GameSettings.h"
#include "ServerWorld.h"
class WorldEditor
{
public:
	//! Constructor
	WorldEditor();
	//! Destructor
	~WorldEditor();
	//! Game window that contains the sprites to place
	GameWindow window;
	
	//! Render GUI
	void Render(GL_Renderer& renderer, World& world, Player& player);




	//! List of cell names in the window
	std::map<int, std::string> cellNames;

	//! list of example cells to get the textures of
	std::vector<Cell> exampleCells;

	//! The list of buttons with the textures of the cells
	std::vector<Button> buttons;

	//! Creates cells based on what spritesheet to render
	void CreateExampleCells();

	//! Cell to highlight where the cell is being placed
	Cell cellHighlight;
	Texture2D highlightTexture;

private:
	//! Selected item in the window
	int selected = -1;
	//! Used for initilising the list of cells
	bool initalisedCells = false;
	//! Button size
	int iconSize = 50;
	bool placeGrass = false;
	bool placeFerns = false;
	bool PlaceHosue = false;
	int selectedLight = -1;
	int placementArea = 1;

	//! Create example cells window
	void CreateExampleSheet(GameWindow& window, std::string spriteSheetName, int totalSprites, glm::vec2 position, glm::vec2 size);
};

