#pragma once
#include "GUI.h"
#include "Button.h"
#include "Inventory.h"
#include "ItemDescriptionWindow.h"
class ItemSelection : public GUI
{
public:
	ItemSelection();
	ItemSelection(Inventory& inventory);
	~ItemSelection();

	static std::map<int, ItemSelection&> ItemSelectionWindows;


	void CreateItemSelection(std::vector<std::vector<std::shared_ptr<Item>>> items);
	void CreateItemSelection(Inventory& inventory);
	// For storing a reference to the object
	Inventory* inventoryPointer = nullptr;

	std::vector<Button> buttons;
	ItemDescriptionWindow itemDescription;

	void Render(GL_Renderer& renderer);
	//! Getters and setter
	int getTotalItems() { return totalItems; }
	int getCurrentSize() { return buttons.size(); }
	int setTotalItems(int newTotal) { return totalItems = newTotal; }

	bool isOpen = false;
private:
	void CreateItemButtons(std::vector<std::vector<std::shared_ptr<Item>>> items);
	void CreateItemButtons(Inventory& inventory);

	int iconSize = 50;
	int totalItems = 20, totalItemsOld;
	int selected = -1;

	//! ID for referencing other Item slections for moving items
	int ID = -1;
	int l_inventorySize = 0;

	
};

