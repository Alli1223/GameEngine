#pragma once
#include "Furniture.h"
class Door : public Furniture
{
public:
	//! Constructor
	Door::Door();
	//! Destructor
	Door::~Door();

	enum Type {
		Entrance,
		Exit
	}type;

	void Render(GL_Renderer& renderer);

private:
	std::string  itemName = "Door";
	std::string  itemDescription = "Door";
	int maximumStackSize = 5;
};

