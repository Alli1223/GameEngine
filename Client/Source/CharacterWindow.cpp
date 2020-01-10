#include "stdafx.h"
#include "CharacterWindow.h"

CharacerWindow::CharacerWindow()
{
	this->setSize(500, 500);
	this->setPosition(500, 500);
	window.itemSelection.setSize({ this->getWidth(), this->getHeight() / 2.0f });
	window.itemSelection.setPosition({ this->getX(), this->getY() + (this->getSize().y / 4) });
	this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
}


CharacerWindow::~CharacerWindow()
{
}

void CharacerWindow::init(Player& player)
{
	if (!initilised)
	{
		colour = { 0,0,0 };
		actualPlayer = &player;
		initilised = true;
		window.itemSelection.inventoryPointer = &player.inventory;
		window.itemSelection.CreateItemSelection(player.inventory.getItemList());
		this->Background = ResourceManager::LoadTexture(imageLocation);
	}
}

void CharacerWindow::Render(GL_Renderer& renderer)
{
	if (isOpen)
	{
		window.isOpen = true;
		renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
		window.Render(renderer);
	}
	else
		window.isOpen = false;
}
