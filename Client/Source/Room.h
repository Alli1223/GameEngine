#pragma once
#include "Instance.h"
#include "Cell.h"
class Room : public Instance
{
	//! Constructor
	Room();
	//! Deconstructor
	~Room();
	//! room tiles
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	//!
};

