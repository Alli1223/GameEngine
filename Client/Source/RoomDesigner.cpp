#include "stdafx.h"
#include "RoomDesigner.h"
#include "GameSettings.h"
RoomDesigner::RoomDesigner() 
{
	GUI.ToggleButton.setPosition({ 0,0 });
	GUI.ToggleButton.setSize({ 50,50 });
	GUI.setSize({ 500,500 });
	GUI.setPosition({ 50,500 });
}
RoomDesigner::~RoomDesigner()
{

}
void RoomResigerGUI::CreateButtons()
{
	

	highlight.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\LuminanceSlider.png");
	highlight.transparency = 0.5f;
	highlight.renderLayer = 4;

	Button newButton;
	Door door;
	newButton.buttonItem.push_back(door.getSharedPointer());
	buttons.push_back(newButton);


	int x = getPosition().x;
	int y = getPosition().y;
	for (int i = 0; i < buttons.size(); i++)
	{
		if (x < getPosition().x + getSize().x)
		{
			x = getPosition().x;
			y += iconSize;

			buttons[i].setPosition({ x,y });
			buttons[i].setSize({ iconSize, iconSize });
		}
	}

	updateButttons = false;
}


void RoomDesigner::Render(GL_Renderer& renderer)
{
	if (GUI.updateButttons)
	{
		GUI.CreateButtons();
		room = (Room*)(GameSettings::currentInstance);
		GUI.cellSize = room->getTileSize();
	}
	GUI.ToggleButton.Render(renderer);
	if (GUI.ToggleButton.isPressed())
	{
		if (GUI.toggleButton == false)
			GUI.toggleButton = true;
		else if (GUI.toggleButton == true)
			GUI.toggleButton = false;
	}
	if (GUI.toggleButton)
	{
		GUI.Render(renderer);
		for (int i = 0; i < GUI.buttons.size(); i++)
		{
			if (GUI.buttons[i].isPressed())
			{
				selectedItem = GUI.buttons[i].buttonItem[0];
			}
			GUI.buttons[i].Render(renderer);
			GUI.buttons[i].buttonItem[0]->icon.setPosition(GUI.buttons[i].getPosition());
			GUI.buttons[i].buttonItem[0]->icon.setSize(GUI.buttons[i].getSize());
			GUI.buttons[i].buttonItem[0]->icon.Render(renderer);
		}
	}

	if (selectedItem != nullptr)
	{
		std::shared_ptr<Door> FurnitureItem = std::dynamic_pointer_cast<Door>(selectedItem);

		if(room != nullptr)
			GUI.cellSize = room->getTileSize();
		int X = 0, Y = 0;
		SDL_GetMouseState(&X, &Y);
		int mX = (X + renderer.camera.getX() + (GUI.cellSize / 2)) / GUI.cellSize;
		int mY = (Y + renderer.camera.getY() + (GUI.cellSize / 2)) / GUI.cellSize;

		GUI.highlight.setPosition(mX * GUI.cellSize, mY * GUI.cellSize);
		GUI.highlight.setSize(GUI.cellSize, GUI.cellSize);
		GUI.highlight.Render(renderer);

		if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			room->SetCellItem(mX, mY, selectedItem);
			//room->tiles[mX][mY]->CellItem = selectedItem;
			selectedItem = nullptr;

		}
	}
}

