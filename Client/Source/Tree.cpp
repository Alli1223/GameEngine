#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
	renderLayer = 3;
	setSize(500, 500);
}
Tree::Tree(json data)
{
	renderLayer = 3;
	setSize(500, 500);

	this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\tree.png");
	this->NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\tree.png");

	this->Stump = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeStump.png");
	this->StumpNormal = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeStump.png");

	this->Leaves = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeLeaves.png");
	this->LeavesNormal = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeLeaves.png");

	float x = data.at("X");
	float y = data.at("Y");
	float w = data.at("W");
	float h = data.at("H");

	setPosition({ x, y });
	setSize({ w,h });
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
	float leafTransp = 1.0f;
	// Turn transparent if player is underneath
	if (GameSettings::currentInstance->I_player.getPosition().y > pos.y - (size.y / 2) && GameSettings::currentInstance->I_player.getPosition().y < pos.y + (size.y / 4))
		if(GameSettings::currentInstance->I_player.getPosition().x > pos.x - (size.x / 2)&& GameSettings::currentInstance->I_player.getPosition().x < pos.x + (size.x / 2))
			leafTransp = 0.25f;



	renderer.RenderSpriteLighting(this->Stump, this->StumpNormal, pos, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
	renderer.RenderSpriteLighting(this->Leaves, this->LeavesNormal, pos, this->size, this->rotation, leafTransp, this->renderLayer, this->colour, flipSprite);
	//renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}

std::shared_ptr<Item> Tree::getSharedPointer()
{
	auto sharedItem = std::make_shared<Tree>(*this); // make shared Item
	return sharedItem;
}
