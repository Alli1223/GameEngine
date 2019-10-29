#pragma once
#include "GUI.h"
#include "Button.h"
#include "Door.h"
#include "Room.h"
class Room;
struct RoomResigerGUI : public GUI
{
	std::vector<Button> buttons;

	Texture2D backgroundTesture;
	bool updateButttons = true;
	bool erase = false;
	int iconSize = 50;

	void CreateButtons();
	
	bool toggleButton = true;
	Button ToggleButton;
	Cell highlight;
	int cellSize = 100;

};
class RoomDesigner 
{
public:
	//! Constructor
	RoomDesigner();
	//! Destroctor
	~RoomDesigner();

	Room* room = nullptr;

	void Render(GL_Renderer& renderer);

	std::shared_ptr<Item> selectedItem = nullptr;

	RoomResigerGUI GUI;




};

