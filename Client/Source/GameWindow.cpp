#include "stdafx.h"
#include "GameWindow.h"


GameWindow::GameWindow() 
{

	imageLocation = "Resources\\UI\\Background.png";
	//this->Background = ResourceManager::LoadTexture("Resources\\UI\\Background.png");
}


GameWindow::~GameWindow()
{
}

void GameWindow::Render(GL_Renderer& renderer)
{
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
