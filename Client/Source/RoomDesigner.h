#pragma once
#include "GUI.h"
#include "Button.h"


struct RoomResigerGUI : public GUI
{
	std::vector<Button> buttons;

	Texture2D backgroundTesture;
	bool updateButttons = true;
	int iconSize = 50;
	

	void Render(GL_Renderer& renderer) 
	{
		if(updateButttons)
			CreateButtons();
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].Render(renderer);
		}
	}

	void CreateButtons()
	{
		for (int i = 0; i < 10; i++)
		{
			Button newButton;
			buttons.push_back(newButton);
		}
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
	bool toggleButton = true;
	Button ToggleButton;
};
class RoomDesigner 
{
public:
	//! Constructor
	RoomDesigner();
	//! Destroctor
	~RoomDesigner();

	void Render(GL_Renderer& renderer);

	RoomResigerGUI GUI;
};

