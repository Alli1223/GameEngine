#pragma once
#include "Furniture.h"
#include "GameWindow.h"
class ShopDisplayShelf : public Furniture
{
public:
	ShopDisplayShelf();
	~ShopDisplayShelf();

	//! Use the item
	void Use(GL_Renderer& renderer, World& world, Player& player);
	//! Runs when items is slected
	void Selected(GL_Renderer& renderer, World& world, Player& player);
	//! Render the item
	void Render(GL_Renderer& renderer);
	//! Render with more options
	//void Render(GL_Renderer& renderer, World& world);

	//! Virtual Getters and Setters
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }
	int getMaximumStackSize() { return maximumStackSize; }
	int getStack() { return stack; }
	int setStack(int newStack) { return stack = newStack; }

	//! Get shared pointer
	std::shared_ptr<ShopDisplayShelf> getShelfPointer();
	std::shared_ptr<Item> ShopDisplayShelf::getSharedPointer();
	// Check if the player has clicked the object
	bool CheckIfPressed(Camera& camera);

	//! Item selection window GUI
	ItemSelection window;

	Inventory shelfInventory;

	//! List of items to sotre in display
	//std::vector<std::shared_ptr<Item>> items;
	//! Add an item
	void AddItem(std::shared_ptr<Item> item);

private:
	std::shared_ptr<ShopDisplayShelf> thisPointerReference = nullptr;
	//! Item name
	std::string itemName = "ShopDisplayShelf";
	//! Item description
	std::string itemDescription = "Shop display shelf";
	//! This stack size
	int stack = 0;
	//! Maximum stackSize
	int maximumStackSize = 5;

	//! Distance needed to close the chest if the player walks away
	float distanceToCloseWindow = 800.0f;

	bool itemsWindow = false;

	bool init = false;
};

