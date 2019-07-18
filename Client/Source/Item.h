#pragma once
#include "GameObject.h"
#include "Icon.h"

class World;
class Player; // Forward decloration to access player
///////////////////////////////////////////////////////////////////////////////////
// Class: Item
// @ Must have name
// @ Must have stack Number
///////////////////////////////////////////////////////////////////////////////////
class Item : public GameObject
{
public:
	//! Constructor
	Item();
	Item(json jsonData);
	//! Destructor
	~Item();

	//! Runs when an item is selected and clicked
	virtual void Use(GL_Renderer& renderer, World& world, Player& player);
	//! Runs when an item is selected
	virtual void Selected(GL_Renderer& renderer, World& world, Player& player);
	std::shared_ptr<Item> getSharedPointer()
	{
		auto sharedItem = std::make_shared<Item>(*this); // make shared Item
		return sharedItem;
	}

	virtual json getItemJson()
	{
		std::cout << "This is a NULL object" << std::endl;
		json itemData;
		itemData["Type"] = "NULL";
		itemData["X"] = getPosition().x;
		itemData["Y"] = getPosition().y;
		return itemData;
	}
	virtual std::string getName() { return itemName; }
	virtual std::string getItemDescription() { return itemDescription; }
	virtual int getMaximumStackSize() { return maximumStackSize; }
	virtual int getStack() { return stack; }
	virtual int setStack(int newStack) { return stack = newStack; }
	virtual void Render(GL_Renderer& renderer);
	virtual void Render(GL_Renderer& renderer, World& world);
	Icon icon;

	bool isInFocus = false;
protected:
	std::string ToolSpriteDirectory = "Resources\\Sprites\\Items\\Tools\\";
	std::string IconSpriteDirectory = "Resources\\Sprites\\Items\\Icons\\";
	//! Item Description
	std::string itemDescription = "Item does not have description overload";
	int stack = 0;
	int maximumStackSize = 20;
private:
	std::string  itemName = "UnspecifiedItem";
	int itemHealth = 100;
};


////////////////////////////////////////////////////////
// Fish Item
////////////////////////////////////////////////////////
struct Fish : Item
{
public:
	Fish::Fish();

	//! Get a shared pointer to this object
	std::shared_ptr<Item> getSharedPointer();
	json getItemJson();
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }
	int getMaximumStackSize() { return maximumStackSize; }
	int getStack() { return stack; }
	int setStack(int newStack) { return stack = newStack; }
	

private:
	std::string itemName = "Fish";
	std::string itemDescription = "Fish Item";
	int maximumStack = 20;
};

////////////////////////////////////////////////////////
// Wheat seeds Item
///////////////////////////////////////////////////////
struct WheatSeeds : Item
{
public:
	WheatSeeds::WheatSeeds();
	
	void Use(GL_Renderer& renderer, World& world, Player& player);

	std::shared_ptr<Item> getSharedPointer();
	json getItemJson();
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }
	int getMaximumStackSize() { return maximumStackSize; }
	int getStack() { return stack; }
	int setStack(int newStack) { return stack = newStack; }

private:
	std::string itemName = "WheatSeeds";
	std::string itemDescription = "Some good ol whole grain wheat seeds";
	int maximumStack = 20;
};

////////////////////////////////////////////////////////
// Sunflower seeds Item
///////////////////////////////////////////////////////
struct SunflowerSeeds : Item
{
public:
	SunflowerSeeds::SunflowerSeeds();

	void Use(GL_Renderer& renderer, World& world, Player& player);

	std::shared_ptr<Item> getSharedPointer();
	json getItemJson();
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }
	int getMaximumStackSize() { return maximumStackSize; }
	int getStack() { return stack; }
	int setStack(int newStack) { return stack = newStack; }

private:
	std::string itemName = "SunflowerSeeds";
	std::string itemDescription = "Sunflower Seeds";
	int maximumStack = 20;
};

////////////////////////////////////////////////////////
// Lavender seeds Item
///////////////////////////////////////////////////////
struct LavenderSeeds : Item
{
public:
	LavenderSeeds::LavenderSeeds();

	void Use(GL_Renderer& renderer, World& world, Player& player);

	std::shared_ptr<Item> getSharedPointer();
	json getItemJson();
	std::string getName() { return itemName; }
	int getMaximumStackSize() { return maximumStackSize; }
	int getStack() { return stack; }
	int setStack(int newStack) { return stack = newStack; }
	std::string getItemDescription() { return itemDescription; }
private:
	std::string itemName = "LavenderSeeds";
	int maximumStack = 20;
	std::string itemDescription = "Lavender Seeds, I wonder what these will grow?";
};