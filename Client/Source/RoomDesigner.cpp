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

	
	Door door;
	Wall wall;

	Button deleteButton("Delete");
	Button wallButton(wall.getSharedPointer());
	Button doorButton(door.getSharedPointer());

	buttons.push_back(wallButton);
	buttons.push_back(doorButton);
	buttons.push_back(deleteButton);

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
				if (GUI.buttons[i].buttonItem.size() > 0)
				{
					selectedItem = GUI.buttons[i].buttonItem[0];
				}
				else
					GUI.erase = true;
			}
			GUI.buttons[i].Render(renderer);
			if (GUI.buttons[i].buttonItem.size() > 0)
			{
				GUI.buttons[i].buttonItem[0]->icon.setPosition(GUI.buttons[i].getPosition());
				GUI.buttons[i].buttonItem[0]->icon.setSize(GUI.buttons[i].getSize());
				GUI.buttons[i].buttonItem[0]->icon.Render(renderer);
			}
		}
	}

	if (selectedItem != nullptr || GUI.erase)
	{
		std::shared_ptr<Door> FurnitureItem = std::dynamic_pointer_cast<Door>(selectedItem);

		if (room != nullptr)
		{
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
				if (selectedItem != nullptr)
				{
					//mouse inside window
					if (X > GUI.getX() - (GUI.getWidth() / 2) && X < GUI.getX() + (GUI.getWidth() / 2) && Y > GUI.getY() - (GUI.getHeight() / 2) && Y < GUI.getY() + (GUI.getHeight() / 2))
					{
					}
					else // outside window
					{
						room->SetCellItem(mX, mY, selectedItem, b2BodyType::b2_staticBody);
						GUI.buttons.erase(GUI.buttons.begin(), GUI.buttons.end());
						selectedItem = nullptr;
						GUI.CreateButtons();
					}
				}

				else if (GUI.erase)
				{
					//mouse inside window
					if (X > GUI.getX() - (GUI.getWidth() / 2) && X < GUI.getX() + (GUI.getWidth() / 2) && Y > GUI.getY() - (GUI.getHeight() / 2) && Y < GUI.getY() + (GUI.getHeight() / 2))
					{
					}
					else // outside window
					{
						room->SetCellItem(mX, mY, nullptr);
						GUI.erase = false;
						selectedItem = nullptr;
					}
				}
			}
		}
	}
}
