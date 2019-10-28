#pragma once
#include "Furniture.h"
class Door : public Furniture
{
public:
	//! Constructor
	Door::Door();
	//! Destructor
	Door::~Door();

	void Render(GL_Renderer& renderer);

	int test();

private:
	std::string  itemName = "Door";
	std::string  itemDescription = "UnspecifiedItem";
	int maximumStackSize = 5;
};

