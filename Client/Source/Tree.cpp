#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
	renderLayer = 3;
	setSize(500, 500);
}

Tree::~Tree()
{
}

json Tree::GetJson()
{
	json itemData;
	itemData["Type"] = itemName;
	itemData["X"] = getPosition().x;
	itemData["Y"] = getPosition().y;
	itemData["W"] = getSize().x;
	itemData["H"] = getSize().y;
	return itemData;
}

void Tree::Render(GL_Renderer& renderer)
{
	//Render from base of tree rather than mid
	glm::vec2 pos = { this->position.x, this->position.y - this->size.y / 2 };
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, pos, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}

std::shared_ptr<Item> Tree::getSharedPointer()
{
	auto sharedItem = std::make_shared<Tree>(*this); // make shared Item
	return sharedItem;
}
