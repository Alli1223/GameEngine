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
};

