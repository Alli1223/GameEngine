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

	json GetJson();

	//! Item name
	std::string itemName = "Wall";
	//! Item description
	std::string itemDescription = "Item does not have description overload";
	
};

