#pragma once
#include "Furniture.h"
class Kiosk : public Furniture
{

public:
	//! Constructor
	Kiosk::Kiosk();
	Kiosk(json data);
	//! Destructor
	Kiosk::~Kiosk();

	json GetJson();

	//! Item name
	std::string itemName = "Kiosk";
	//! Item description
	std::string itemDescription = "Item does not have description overload";

};

