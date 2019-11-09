#include "stdafx.h"
#include "RoomDesigner.h"
#include "GameSettings.h"
RoomDesigner::RoomDesigner() 
{
	GUI.ToggleButton.setPosition({ 0,0 });
	GUI.ToggleButton.setSize({ 50,50 });
	GUI.setSize({ 500,500 });
	GUI.setPosition({ 50,500 });

	GUI.shopManagement.setPosition({ 1600,500 });
	GUI.shopManagement.setSize({ 250,100 });
	GUI.shopManagement.isOpen = true;
}
RoomDesigner::~RoomDesigner()
{

}
void RoomResigerGUI::CreateButtons()
{
	shopManagement.Background = ResourceManager::LoadTexture("Resources\\UI\\Background.png");
	
	highlight.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\LuminanceSlider.png");
	highlight.transparency = 0.5f;
	highlight.renderLayer = 4;

	
	Door door;
	Wall wall;
	ActionItem deleteAction(ActionItem::action::Delete);
	ActionItem moveAction(ActionItem::action::Move);

	Button deleteButton(moveAction.getSharedPointer());
	Button moveButton(deleteAction.getSharedPointer());
	Button wallButton(wall.getSharedPointer());
	Button doorButton(door.getSharedPointer());

	buttons.push_back(wallButton);
	buttons.push_back(doorButton);
	buttons.push_back(moveButton);
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
		x += buttons[i].getSize().x;
	}
	updateButttons = false;

	// Shop Managerment
	Button HireStaff("Hire");
	shopManagement.buttons.push_back(HireStaff);
	for (int i = 0; i < shopManagement.buttons.size(); i++)
	{
		shopManagement.buttons[i].setPosition({ shopManagement.getPosition().x , shopManagement.getPosition().y});
	}
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
			GUI.toggleButton = true, GUI.shopManagement.isOpen = true;
		else if (GUI.toggleButton == true)
			GUI.toggleButton = false, GUI.shopManagement.isOpen = false;
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
					GUI.selected = true;
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
	if (GUI.shopManagement.isOpen)
	{
		GUI.shopManagement.Render(renderer);

		// Hire Staff
		if (GUI.shopManagement.buttons[0].isPressed() && SDL_GetTicks() > GUI.timeItemPressed + 300.0f)
		{
			GUI.timeItemPressed = SDL_GetTicks();
			Shopkeeper newStaff;
			room->SpawnNPC(newStaff.getSharedPointer());
		}

	}
	if (selectedItem != nullptr)
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
						if(GUI.selected == true)
							GUI.selected = false;
					}
					else // outside window
					{
						if (selectedItem->getName() == "Move")
						{
							// Select item
							if (GUI.selected == false)
							{
								GUI.timeItemPressed = SDL_GetTicks();
								tempItem = room->GetCell(mX, mY)->CellItem;
								GUI.selected = true;
								room->SetCellItem(mX, mY, nullptr);
							}
							else // palce selected
							{
								if (tempItem != nullptr && SDL_GetTicks() > GUI.timeItemPressed + 250.0f) // only place after 250ms has expired to avoid placing back down in same space
								{
									// Place item
									//tempItem->setPosition({ mX, mY });
									room->SetCellItem(mX, mY, tempItem);
									tempItem = nullptr;
									selectedItem = nullptr;
									GUI.selected = false;
								}
							}
						}
						else if (selectedItem->getName() == "Delete") 
						{
							// Remove item
							room->SetCellItem(mX, mY, nullptr);
							GUI.selected = false;
							selectedItem = nullptr;
							GUI.buttons.erase(GUI.buttons.begin(), GUI.buttons.end());
							GUI.CreateButtons();
						}
						else
						{
							// Place item
							room->SetCellItem(mX, mY, selectedItem, selectedItem->bodyType);
							GUI.buttons.erase(GUI.buttons.begin(), GUI.buttons.end());
							selectedItem = nullptr;
							GUI.CreateButtons();
						}
					}
				}
			}
		}
	}
}

ActionItem::ActionItem(ActionItem::action action)
{
	std::string directory = "null";
	switch (action)
	{
	default:
		break;
	case ActionItem::Move:
		directory = UISpriteDirectory + "R_Button.png";
		this->setName("Move");
		this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
		break;
	case ActionItem::Delete:
		directory = UISpriteDirectory + "NoButton.png";
		this->setName("Delete");
		this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
		break;
	}

}
