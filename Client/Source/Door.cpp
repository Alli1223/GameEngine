#include "stdafx.h"
#include "Door.h"

Door::Door()
{
	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 678);
	this->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 678);

	std::string directory = IconSpriteDirectory + "ShopDisplayShelf.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());
	renderLayer = 3;
}

Door::~Door()
{
}

void Door::Render(GL_Renderer& renderer)
{

	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}

