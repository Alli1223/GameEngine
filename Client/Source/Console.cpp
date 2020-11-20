#include "stdafx.h"
#include "Console.h"

//Static log
std::vector<std::string> Console::textLog;

void Console::Init(GameSettings& gs)
{
	//Text Size Factor
	float TSF = textSize * (gs.WINDOW_HEIGHT / 1500.0f);
	setSize(gs.WINDOW_HEIGHT /2.0f, gs.WINDOW_HEIGHT / 4.0f );
	textSize = TSF;
	setPosition(getSize().x /2, gs.WINDOW_HEIGHT - getSize().y);
	this->Background = ResourceManager::LoadTexture("Resources\\UI\\Windows\\panel1.png");
	//setColour({ 255,255,255 });
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
		if (textLog.size() * (textSize * 100) > size.y / 2.5f)
		{
			textLog.erase(textLog.begin() + i);
			break;
		}

		// Good luck reading that
		renderer.RenderText(textLog[i], { (getPosition().x - getSize().x / 2) + (getSize().x / 10), (getPosition().y + (getSize().y / 2) + (getSize().y / 10)) + (i * (textSize * 100) - textLog.size() * (textSize * 100)) - (getSize().y / 3) }, getSize(), { textSize,textSize }, { 255,255,255 });
	}
}
