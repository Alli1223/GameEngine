#pragma once
#include "Furniture.h"
class Wall : public Furniture
{
public:
	//! Constructor
	Wall::Wall();
	Wall(json data);
	//! Destructor
	Wall::~Wall();

	//! Get Item Json
	json GetJson() override;

	//! Get pointer
	std::shared_ptr<Item> getSharedPointer();

	//! Item name
	std::string itemName = "Wall";
	//! Item description
	std::string itemDescription = "Item does not have description overload";
	
};

