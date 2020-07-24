#pragma once
#include "player.h"
#include "GameSettings.h"
#include "ToolBar.h"
#include "CraftingUI.h"
#include "WorldEditor.h"
#include "CharacterWindow.h"
#include "Console.h"
#include "Tree.h"

////////////////////////////////////////////////////////////////////////////
//! Handles the ingame UI
////////////////////////////////////////////////////////////////////////////

class GameUI
{
public:
	//! Consyructor
	GameUI();
	//! Destructor
	~GameUI();

	//! Initilise
	void Init(Player& player, GameSettings& gs);

	//! World editor
	WorldEditor worldEdit;
	//! Toolbar object
	ToolBar toolbar;
	//! Character screen
	CharacerWindow characterWindow;

	GameWindow inventoryWindow;

	//! Room Designer
	RoomDesigner roomDesigner;

	//! Console to write to
	Console console;

	//Function that renders all the UI elements
	void Render(GL_Renderer& renderer, World& world, Player& player, GameSettings& gameSettings);

};

