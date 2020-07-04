#pragma once
#include "GUI.h"
#include "Icon.h"
#include "Button.h"
#include "ItemSelection.h"
class GameWindow : public GUI
{
public:
	//! Constructor
	GameWindow();
	//! Destructor
	~GameWindow();

	ItemSelection itemSelection;

	//! Render the game window
	void Render(GL_Renderer& renderer);

	//! List of icons in the window
	std::vector<Icon> icons;
	//! List of buttons in the window
	std::vector<Button> buttons;

	//! Whether the window is open
	bool isOpen = false;
};

