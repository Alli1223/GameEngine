#pragma once
#include "player.h"
#include "GameSettings.h"
#include "ToolBar.h"
#include "CraftingUI.h"
#include "WorldEditor.h"
#include "CharacterWindow.h"
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

	//! World editor
	WorldEditor worldEdit;
	//! Toolbar object
	ToolBar toolbar;
	//! Character screen
	CharacerWindow characterWindow;

	GameWindow inventoryWindow;

	//Function that renders all the UI elements
	void Render(GL_Renderer& renderer, World& world, Player& player, GameSettings& gameSettings);

};

