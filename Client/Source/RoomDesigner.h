#pragma once
#include "GUI.h"
#include "Button.h"
#include "Door.h"
#include "Room.h"
#include "Kiosk.h"
#include "GameWindow.h"
class Room;

//! Action to set for a button
struct ActionItem : public Item
{
public:
	enum action
	{
		Move,
		Delete
	} actionType;

	//! Construct with an item
	ActionItem::ActionItem(ActionItem::action action);
};
struct RoomResigerGUI : public GUI
{
	std::vector<Button> buttons;

	Texture2D backgroundTesture;
	bool updateButttons = true;
	bool selected = false;
	int iconSize = 50;

	void CreateButtons();
	
	bool toggleButton = true;
	Button ToggleButton;
	Cell highlight;
	int cellSize = 100;

	float timeItemPressed;

	GameWindow shopManagement;
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
	std::shared_ptr<Item> tempItem = nullptr;
	RoomResigerGUI GUI;




};

