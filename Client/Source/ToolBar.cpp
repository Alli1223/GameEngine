#include "stdafx.h"
#include "ToolBar.h"


ToolBar::ToolBar() 
{

	this->imageLocation = "Resources\\UI\\CharacterSheet\\UIButton_Plain.png";
}


ToolBar::~ToolBar()
{
}


bool ToolBar::removeToolbarItem(int index)
{
	if (index < toolbarIcons.size())
	{
		toolbarIcons.erase(toolbarIcons.begin() + index);
		return true;
	}
	else
		return false;
}

void ToolBar::Render(GL_Renderer& renderer, World& world, Player& player, GameSettings& gameSettings)
{
	if (!isInitalised)
		Initalise(), this->selectionTexture = ResourceManager::LoadTexture("Resources\\UI\\CharacterSheet\\UIButton_Normal.png");
	// Render background
	renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
	// Create the toolbar
	if (numberOfIcons != player.inventory.getCurrentSize())
		createToolbar(player, gameSettings);
	for (int i = 0; i < numberOfIcons; i++)
	{
		if (player.inventory.getStack(i).size() > 0)
		{
			toolbarIcons[i]->Background = player.inventory.get(i)->icon.Background;
			toolbarIcons[i]->Render(renderer);

			player.inventory.get(i)->Render(renderer, world);

			player.inventory.get(i)->isInFocus = false;
		}
	}

	// Toolbar selection texture
	if (toolbarSelection >= toolbarIcons.size())
		toolbarSelection = 0;
	if (toolbarSelection < 0)
		toolbarSelection = toolbarIcons.size();

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if(toolbarIcons.size() > 0)
			player.inventory.get(toolbarSelection)->Use(renderer, world, player);
	}

	if (toolbarSelection < toolbarIcons.size() && toolbarSelection >= 0)
	{
		if (player.inventory.getStack(toolbarSelection).size() > 0)
		{
			player.inventory.get(toolbarSelection)->isInFocus = true;
			player.inventory.get(toolbarSelection)->Selected(renderer, world, player);
		}
		renderer.RenderGUI(this->selectionTexture, this->toolbarIcons[toolbarSelection]->getPosition(), this->toolbarIcons[toolbarSelection]->getSize(), this->rotation, 0.5f, this->colour, this->flipSprite);
	}
}

void ToolBar::createToolbar(Player& player, GameSettings& gameSettings)
{
	int WW = gameSettings.WINDOW_WIDTH;
	int WH = gameSettings.WINDOW_HEIGHT;
	if (player.inventory.getCurrentSize() < numberOfIcons)
		numberOfIcons = player.inventory.getCurrentSize();
	toolbarIcons.clear();
	this->setPosition({ WW / 2, iconSize / 2 });
	this->setSize({ (numberOfIcons * iconSize) + iconSize, iconSize + (iconSize / 2) });
	for (int i = 0; i < numberOfIcons; i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);

			
		sharedIcon->setX(getX() - (WW / 8) + (i * iconSize));
		sharedIcon->setY(getY());
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		toolbarIcons.push_back(sharedIcon);
	}

}

