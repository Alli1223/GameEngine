#pragma once
#include "GUI.h"
#include "GameWindow.h"
#include "Inventory.h"
#include "Player.h"
#include "ItemSelection.h"
class CharacerWindow : public GUI
{
public:
	CharacerWindow();
	~CharacerWindow();
	//! Player to display in the character window
	Player characterWindowPlayer;
	//! Pointer to actual player
	Player* actualPlayer = nullptr;
	//! Init
	void init(Player& player);
	//! game window to store buttons
	GameWindow window;

	void Render(GL_Renderer& renderer);

	bool isOpen = false;
private:
	int selected = -1;
	int iconSize = 50;
	
	bool initilised = false;
};

