#include "stdafx.h"
#include "Button.h"

Button::Button()
{
	//this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
	this->setPosition(500, 500);
	this->setSize(50, 50);
}
Button::Button(std::string buttonText, glm::vec2 position, std::string textureLocation, glm::vec2 size, glm::vec3 buttonColour, glm::vec3 textColour)
{
	if (buttonText.size() > 0)
		text = buttonText;

	this->position = position;
	this->Background = ResourceManager::LoadTexture(textureLocation);
	this->size = size;
	this->setColour(buttonColour);
	this->textColour = textColour;
}
Button::Button(std::string newText) : text(newText)
{
	//this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
	this->setPosition(500, 500);
	this->setSize(50, 50);
	this->textColour = { 0.5,1.0,1.0 };
}
Button::Button(std::string newText, std::string backgroundType) :  text(newText)
{

}

Button::Button(std::shared_ptr<Item>& item)
{
	buttonItem.push_back(item);
}

Button::~Button()
{
	
}
bool Button::isPressed()
{
	UpdateInfo();
	if (isActivated)
	{
		isActivated = false;
		return true;
	}
	else
		return false;
}

bool Button::isHovered()
{
	UpdateInfo();
	if (isMouseOver)
		return true;
	else
		return false;
}

void Button::UpdateInfo()
{
	SDL_GetMouseState(&tx, &ty);
	if (SDL_GetTicks() / 1000.0 > timeButtonWasPressed + buttonTimeout)
	{
		isActivated = false;
		timeout = false;
		timeButtonWasPressed = 0;
	}

	if (tx > getX() - (getWidth() / 2) && tx < getX() + (getWidth() / 2) && ty > getY() - (getHeight() / 2) && ty < getY() + (getHeight() / 2))
	{
		// Mouse hover over
		isMouseOver = true;
		// Activate the button if it has been pressed
		if (SDL_GetMouseState(&tx, &ty) & SDL_BUTTON(SDL_BUTTON_LEFT) && !timeout)
		{
			isActivated = true;
			timeButtonWasPressed = SDL_GetTicks() / 1000.0;
			timeout = true;
		}
	}
	else
		isMouseOver = false;
}

void Button::ButtonPressed()
{
	if (runOnceUpdate)
	{
		oldColour = getColour();
		setColour(getColour() - 10.0f);
		runOnceUpdate = false;
	}
}

void Button::Render(GL_Renderer& renderer)
{
	if (!isInitalised)
		Initalise();
	// Set object variables
	UpdateInfo();

	if (isActivated)
	{
		ButtonPressed();
	}
	else
	{
		if(!runOnceUpdate)
			setColour(oldColour);
		runOnceUpdate = true;
	}
	
	// If the button has text, render it in the center of the button
	renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, this->flipSprite);
	if (text.size() > 0)
		renderer.RenderText(text, { this->position.x , position.y + size.y / 4 }, this->size, { textSize, textSize }, textColour);
		//buttonText.render(renderer, text, getX() - (getWidth() / 2) +(getWidth() / 20), getY() - (getHeight() / 2) + (getHeight() / 5), getWidth() - (getWidth() / 10) / 2, getHeight() / 2, buttonTextColour);
}

