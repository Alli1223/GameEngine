#include "stdafx.h"
#include "Inventory.h"


Inventory::Inventory()
{
	// create an empty list
	for (int i = 0; i < capacity; i++)
	{
		std::vector<std::shared_ptr<Item>> newItem;
		newItem.clear();
		items.push_back(newItem);
	}
}
Inventory::~Inventory()
{
}

bool Inventory::add(std::vector<std::shared_ptr<Item>>& newItems, unsigned int position)
{
	if (position > 0 && position < capacity)
	{
		if (items[position].size() > 0)
		{
			if (newItems.front()->getName() == items[position].front()->getName()) // items are the same
			{
				for (int i = 0; i < newItems.size(); i++) // Loop through the new items and add them
				{
					if (items[position].size() < items[position].front()->getMaximumStackSize()) // there is space
					{
						items[position].push_back(newItems[i]);
						newItems.erase(newItems.begin() + i);
					}
				}
				return true;
			}
		}
		else // if not the same, insert that item
		{
			items[position] = newItems;
			return true;
		}

	}
	return false;
}
bool Inventory::add(std::shared_ptr<Item>& item)
{
	// Add to existing stack
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].size() > 0) // if there is an item
		{
			std::string inventoryItemName = get(i)->getName();
			std::string itemToAddsName = item->getName();
			int maxStack = item->getMaximumStackSize();

			if (get(i)->getName() == item->getName() && getItemStackSize(i) < item->getMaximumStackSize() && get(i)->getName() != "") // if same item
			{
				items[i].push_back(item); // add it
				return true;
			}
		}
	}

	// Add to new stack
	if (capacity > getCurrentSize())
	{
		std::vector<std::shared_ptr<Item>> newStack;
		newStack.push_back(item);
		for (int i = 0; i < capacity; i++) // find an empty space
			if (items[i].size() == 0)
			{
				items[i] = newStack;
				return true;
			}
	}

	// cant do either
	return false;
}

bool Inventory::add(std::vector<std::shared_ptr<Item>>& newStack)
{
	for (int i = 0; i < capacity; i++) // find an empty space
		if (items[i].size() == 0)
		{
			items[i] = newStack;
			return true;
		}
}
std::shared_ptr<Item>& Inventory::get(unsigned int index)
{
	return items.at(index).front();
}
std::vector<std::vector<std::shared_ptr<Item>>>& Inventory::getVectorOfOnlyTheItems()
{
	std::vector<std::vector<std::shared_ptr<Item>>> itemList;
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].size() > 0)
			itemList.push_back(items[i]);
	}
	return itemList;
}
std::vector<std::shared_ptr<Item>>& Inventory::getStack(unsigned int index)
{
	return items.at(index);
}

unsigned int Inventory::getItemStackSize(unsigned int index)
{
	return items.at(index).size();
}

void Inventory::swap(unsigned int first, unsigned int second)
{
	std::iter_swap(items.begin() + first, items.begin() + second);
}

bool Inventory::move(Inventory& inventory, unsigned int thisIndex, unsigned int newInventoryIndex)
{
	if (items[thisIndex].size() > 0) // the selected item exists
	{
		if (newInventoryIndex < inventory.getCapacity()) // there is space in the new inventory
		{
			if(inventory.getStack(newInventoryIndex).size() > 0)
				if (items[thisIndex].front()->getName() == inventory.get(newInventoryIndex)->getName()) // items are the same
				{
					for (int i = 0; i < items[thisIndex].size(); i++) // Loop through the new items and add them
					{
						if (inventory.getStack(newInventoryIndex).size() < items[thisIndex].front()->getMaximumStackSize()) // there is space
						{
							inventory.add(items[thisIndex], newInventoryIndex);
							//newItems.erase(newItems.begin() + i);
						}
					}
					return true;
				}
			
			inventory.add(items[thisIndex], newInventoryIndex); // add to new inventory
			items[thisIndex].clear(); // remove this one
			return true;
		}
	}
	return false;
}
unsigned int Inventory::getCurrentSize()
{
	int size = 0;
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].size() > 0)
			++size;
	}
	return size;
}



bool Inventory::remove(unsigned int index)
{
	if (index < items.size())
	{
		items.erase(items.begin() + index);
		return true;
	}
	return false;
}
bool Inventory::removeItem(std::shared_ptr<Item>& item)
{
	for (int i = 0; i < getCurrentSize(); i++)
		if (get(i)->getName() == item->getName())
		{
			if (get(i)->getStack() > 0)
				get(i)->setStack(get(i)->getStack() - 1);
			else
				remove(i);
			return true;
		}
	return false;
}

unsigned int Inventory::setCapacity(unsigned int newCapacity)
{
	// Reararange the items to fit the new capacity
	std::vector<std::vector<std::shared_ptr<Item>>> overflowItems;
	for (int i = newCapacity; i < capacity; i++) // get all the elements and move them
		if (items[i].size() > 0)
		{
			overflowItems.push_back(items[i]);
		}

	if (overflowItems.size() > 0)
	{
		int counter = 0;
		for (int q = 0; q < newCapacity; q++)
			if (items[q].size() == 0)
			{
				items[q] = overflowItems[counter];
				counter++;
			}
	}
	return capacity = newCapacity;
}

std::vector<std::vector<std::shared_ptr<Item>>>& Inventory::getItemList()
{
	return items;
}
