#include "stdafx.h"
#include "GUI.h"



GUI::GUI()
	: position(0, 0), size(10, 10), colour(0.0f), rotation(0.0f), Background() { }
GUI::GUI(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: position(pos), size(size), colour(color), rotation(0.0f), Background(sprite) { }


GUI::~GUI()
{
}

void GUI::Render(GL_Renderer& renderer)
{

	renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
}

void GUI::Update()
{
}

bool GUI::isMouseOver()
{
	bool result = false;
	SDL_GetMouseState(&m_x, &m_y);
	if (m_x > getX() - (getWidth() / 2) && m_x < getX() + (getWidth() / 2) && m_y > getY() - (getHeight() / 2) && m_y < getY() + (getHeight() / 2))
	{
		result = true;
	}
	return result;
}

void GUI::Initalise()
{
	if (imageLocation > 0)
		this->Background = ResourceManager::LoadTexture(imageLocation);
	isInitalised = true;

}
