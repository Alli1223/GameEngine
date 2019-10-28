#pragma once
#include "GUI.h"
#include "Button.h"
#include "Door.h"

struct RoomResigerGUI : public GUI
{
	std::vector<Button> buttons;

	Texture2D backgroundTesture;
	bool updateButttons = true;
	int iconSize = 50;

	void CreateButtons();
	
	bool toggleButton = true;
	Button ToggleButton;
};
class RoomDesigner 
{
public:
	//! Constructor
	RoomDesigner();
	//! Destroctor
	~RoomDesigner();

	void Render(GL_Renderer& renderer);

	std::shared_ptr<Item> selectedItem;

	RoomResigerGUI GUI;
};

