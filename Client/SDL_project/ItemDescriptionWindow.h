#pragma once
#include "GUI.h"
#include "Item.h"
class ItemDescriptionWindow : public GUI
{
public:

	ItemDescriptionWindow();
	~ItemDescriptionWindow();

	void Render(GL_Renderer& renderer);
	//! Whether to show this window
	bool showWindow = false;

	//! Text size
	float textSize = 0.2f;

	//! Pointer to item of which has the description
	std::shared_ptr<Item> item = nullptr;
};

