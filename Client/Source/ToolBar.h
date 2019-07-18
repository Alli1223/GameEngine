#pragma once
#include "GUI.h"
#include "Icon.h"
#include "GameSettings.h"


class ToolBar : public GUI
{
public:
	ToolBar();
	~ToolBar();
	
	void Render(GL_Renderer& renderer);
	//! Function that renders the toolbar
	void Render(GL_Renderer& renderer, World& world, Player& player, GameSettings& gameSettings);

	std::vector<std::shared_ptr<Icon>> toolbarIcons;

	//! Remove item from toolbar
	bool removeToolbarItem(int index);

	void createToolbar(Player& player, GameSettings& gameSettings);

	int getToolbarSelection() { return toolbarSelection; }
	int setToolbarSelection(int newSelection) { return toolbarSelection = newSelection; }

	int numOfItems;

private:
	Texture2D selectionTexture;
	int toolbarSelection = 0;
	int numberOfIcons = 10;
	bool toolbarRender = true;
	int iconSize = 50;

};

