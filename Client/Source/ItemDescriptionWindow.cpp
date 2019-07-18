#include "stdafx.h"
#include "ItemDescriptionWindow.h"


ItemDescriptionWindow::ItemDescriptionWindow()
{
	this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
	this->setSize(200, 100);
	this->transparency = 0.8f;
}


ItemDescriptionWindow::~ItemDescriptionWindow()
{
}

void ItemDescriptionWindow::Render(GL_Renderer& renderer)
{
	if (showWindow)
	{
		if (!isInitalised)
			Initalise();
		// Render this background
		renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
		if (item != nullptr)
			if(item->getItemDescription().length() > 0)
			renderer.RenderText(item->getItemDescription(), { this->position.x - size.x / 2, position.y }, this->size, { textSize, textSize }, { 0.5,1.0,1.0 });
	}
}