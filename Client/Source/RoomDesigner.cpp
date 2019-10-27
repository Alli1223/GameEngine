#include "stdafx.h"
#include "RoomDesigner.h"

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

void RoomDesigner::Render(GL_Renderer& renderer)
{

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

			}
			GUI.buttons[i].Render(renderer);
		}
	}

}