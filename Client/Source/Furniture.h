#pragma once
#include "Item.h"
//Inherits this: ShopDisplayShelf.h,ShopDisplayShelf.cpp
#include "Cell.h"

// forward decloration
class Cell;

class Furniture : public Item
{
public:
	//! Constuctor
	Furniture();
	//! desturctor
	~Furniture();

	//! Use the item
	virtual void Use(GL_Renderer& renderer, World& world, Player& player);
	virtual void Selected(GL_Renderer& renderer, World& world, Player& player);
	//! Render the item
	virtual void Render(GL_Renderer& renderer);
	//! Render with more options
	virtual void Render(GL_Renderer& renderer, World& world);

	//! Virtual Getters and Setters
	virtual std::string getName() { return itemName; }
	virtual std::string getItemDescription() { return itemDescription; }
	virtual int getMaximumStackSize() { return maximumStackSize; }
	virtual int getStack() { return stack; }
	virtual int setStack(int newStack) { return stack = newStack; }

	void Place(Cell& cell);


private:
	//! Item name
	std::string itemName = "Furniture";	
	//! Item description
	std::string itemDescription = "Item does not have description overload";
	//! This stack size
	int stack = 0;
	//! Maximum stackSize
	int maximumStackSize = 20;
};


