#pragma once
#include "Item.h"
#include "player.h" // Able to get from forward decloration
class Tool : public Item
{
public:
	Tool();
	~Tool();
	virtual void Use(GL_Renderer& renderer, World& world, Player& player);

	virtual std::string getName() { return itemName; }
private:
	std::string itemName = "Tool";

};
//////////////////////////////////////////////////////////////////////
// Hoe
//////////////////////////////////////////////////////////////////////
struct Hoe : public Tool
{	
	bool inUse = false;
	//Cell highlight;
	Hoe::Hoe();
	std::shared_ptr<Item> getSharedPointer();
	void Render(GL_Renderer& renderer, World& world);

	void Use(GL_Renderer& renderer, World& world, Player& player);
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }

private:
	int offset = 0;
	bool flipSprite = false;
	std::string itemName = "Hoe";
	std::string itemDescription = "A basic hoe";
	int maximumStackSize = 1;
};

//////////////////////////////////////////////////////////////////////
// BugNet
//////////////////////////////////////////////////////////////////////
struct BugNet : public Tool
{
	//! Constructor
	BugNet::BugNet();
	//! Get shared pointer
	std::shared_ptr<Item> getSharedPointer();

	//! Render function
	void Render(GL_Renderer& renderer, World& world);

	//! Use the item
	void Use(GL_Renderer& renderer, World& world, Player& player);
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }
private:
	enum CastDirection
	{
		none, left, right, up, down
	} castDirection;
	Animation castingAnim;

	bool flipSprite = false;

	std::string itemName = "BugNet";
	std::string itemDescription = "A basic Bug net, for catching pesky bees";
	int maximumStackSize = 1;
};


//////////////////////////////////////////////////////////////////////
// Scythe
//////////////////////////////////////////////////////////////////////
struct Scythe : public Tool
{
	//! Constructor
	Scythe::Scythe();
	//! Get shared pointer
	std::shared_ptr<Item> getSharedPointer();
	//! Render function
	void Render(GL_Renderer& renderer, World& world);
	//! Use the item
	void Use(GL_Renderer& renderer, World& world, Player& player);
	std::string getName() { return itemName; }
	std::string getItemDescription() { return itemDescription; }

private:
	enum CastDirection
	{
		none, left, right, up, down
	} castDirection;
	Animation castingAnim;

	bool flipSprite = false;
	std::string itemName = "Scythe";
	std::string itemDescription = "A basic scythe";
	int maximumStackSize = 1;
};