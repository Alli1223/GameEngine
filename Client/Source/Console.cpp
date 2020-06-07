#include "stdafx.h"
#include "Console.h"

//Static log
std::vector<std::string> Console::textLog;

void Console::Init(GameSettings& gs)
{
	setSize(300, 100);
	setPosition(150, gs.WINDOW_HEIGHT / 4);
	this->Background = ResourceManager::LoadTexture("Resources\\UI\\CharacterSheet\\IconBorder.png");
}

void Console::Print(std::string text)
{
	textLog.push_back(text);
}

void Console::Render(GL_Renderer& renderer)
{
	renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
	for (int i = 0; i < textLog.size(); i++)
	{
		renderer.RenderText(textLog[i], { getPosition().x - getSize().x / 2, getPosition().y - (i * (textSize * 100)) }, getSize(), { textSize,textSize }, { 255,255,255 });
	}
}
