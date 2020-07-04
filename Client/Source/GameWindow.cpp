#include "stdafx.h"
#include "GameWindow.h"


GameWindow::GameWindow() 
{

	imageLocation = "Resources\\UI\\Windows\\panel1.png";
	//this->Background = ResourceManager::LoadTexture("Resources\\UI\\Windows\\panel1.png");
}


GameWindow::~GameWindow()
{
}

void GameWindow::Render(GL_Renderer& renderer)
{
	if(this->Background.Height> 0 && this->Background.Width > 0)
		renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
	itemSelection.Render(renderer);
	if (buttons.size() > 0)
	{
		for (auto button : buttons)
		{
			button.Render(renderer);
		}
	}

}
