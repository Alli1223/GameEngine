#include "stdafx.h"
#include "Furniture.h"


Furniture::Furniture()
{
}


Furniture::~Furniture()
{
}
void Furniture::Render(GL_Renderer& renderer)
{
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}
void Furniture::Render(GL_Renderer& renderer, World& world)
{
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}
void Furniture::Place(Cell& cell)
{
	renderLayer = 3;
	cell.CellItem = getSharedPointer();
	setSize(cell.getSize());
	setPosition(cell.getPosition());
}
void Furniture::Use(GL_Renderer& renderer, World& world, Player& player)
{

}

void Furniture::Selected(GL_Renderer & renderer, World & world, Player & player)
{
}
