#include "stdafx.h"
#include "SpeechBubble.h"
SpeechBubble::SpeechBubble()
{
	this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
	this->Background = ResourceManager::LoadTexture(imageLocation);
	this->size = { 100,300 };
}
SpeechBubble::~SpeechBubble()
{
}

void SpeechBubble::Render(GL_Renderer& renderer)
{
	// Render in relation to camera
	if (text.size() > 0)
	{
		//renderer.RenderGUI(this->Background, this->position - renderer.camera.getPosition(), this->size, this->rotation, this->transparency, this->colour, flipSprite);

		renderer.RenderText(text, { (this->position.x -renderer.camera.getPosition().x) - size.x / 2, position.y - renderer.camera.getPosition().y }, this->size, { textSize, textSize }, { 0.5,1.0,1.0 });
	}

}
