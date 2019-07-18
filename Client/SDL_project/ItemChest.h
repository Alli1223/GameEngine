#pragma once
#include "GameObject.h"
#include "Inventory.h"
#include "GameWindow.h"
class ItemChest : public GameObject
{
public:
	ItemChest();
	~ItemChest();

	// Inventory of items in the chest
	Inventory inventory;
	//! Item selection window
	ItemSelection window;

	// Check if the player has clicked the object
	bool CheckIfPressed(Camera& camera);
	void Init();
	//! Render the chest and GUI
	void Render(GL_Renderer& renderer);

	//! Get and Set inventory size
	int getInventorySize() { return inventorySize; }
	int setInventorySize(int newSize) { return inventorySize = newSize; }
private:
	//! Inventory size of the chest
	int inventorySize = 15;

	//! Distance needed to close the chest if the player walks away
	float distanceToClose = 125.0f;

	//! Whether the chest has been opened
	bool isOpen = false;
};

