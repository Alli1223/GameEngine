#pragma once
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	//! Add an item at a specified index
	bool add(std::vector<std::shared_ptr<Item>>& newItems, unsigned int position);

	// Add item
	bool add(std::shared_ptr<Item>& item);


	// Add two stacks together
	bool add(std::vector<std::shared_ptr<Item>>& newStack);


	// returns the size of inventory
	unsigned int getCapacity() const
	{
		return capacity;
	}

	//Get size of the current inventory
	unsigned int getCurrentSize();


	// Returns first element in the list
	std::shared_ptr<Item>& get(unsigned int index);

	//! Returns a list of only the items in the inventory
	std::vector<std::vector<std::shared_ptr<Item>>>& getVectorOfOnlyTheItems();

	// Returns list of items in the stack
	std::vector<std::shared_ptr<Item>>& getStack(unsigned int index);

	//! get amount of items in a specified stack
	unsigned int getItemStackSize(unsigned int index);

	//! Swap two items in the inventory
	void swap(unsigned int from, unsigned int to);

	//! Move an item to another inventory
	bool move(Inventory& inventory, unsigned int thisIndex, unsigned int newInventoryIndex);


	// Returns true if the index was removed, false if the index was out of bounds
	bool remove(unsigned int index);
	
	// Remove an item from the inventory
	bool removeItem(std::shared_ptr<Item>& item);

	//! Set inventory to a new size
	unsigned int setCapacity(unsigned int newCapacity);

	//! Get the list of all the items in inventory (including null items)
	std::vector<std::vector<std::shared_ptr<Item>>>& getItemList();

	
private:
	unsigned int capacity = 50;
	std::vector<std::vector<std::shared_ptr<Item>>> items;

};

