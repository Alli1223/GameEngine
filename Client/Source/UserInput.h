#pragma once
#include "player.h"
#include "ToolBar.h"
#include "Timer.h"
#include "GameUI.h"
class UserInput
{
public:
	//! Constructor
	UserInput();
	//! Destructor
	~UserInput();

	Inventory craftingInventory;

	void UserInput::HandleUserInput(GL_Renderer& renderer, Player& player, GameSettings& gameSettings, GameUI& UI);
private:
	//! Timers for UIs to have a timeout when opened or closed
	Timer inventoryTimer;
	Timer craftingTimer;
	//! Timeout in milliseconds
	float inventoryTimeout = 100;
	float craftingTimeout = 100;
	glm::vec2 playerChunkPos;
	glm::vec2 playercellPos;
	glm::vec2 InterDir;

	SDL_Joystick *joystick;
};
