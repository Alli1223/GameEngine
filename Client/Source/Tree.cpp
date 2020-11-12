#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
	renderLayer = 3;
	setSize(500, 500);
	bodyType = b2BodyType::b2_staticBody;
}
Tree::Tree(json data)
{
	renderLayer = 3;
	//setSize(500, 500);

	this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\tree.png");
	this->NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\tree.png");

	this->Stump = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeStump.png");
	this->StumpNormal = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeStump.png");

	this->Leaves = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\TreeLeaves2.png");
	this->LeavesNormal = ResourceManager::LoadTexture("Resources\\Sprites\\Terrain\\treeLeaves.png");

	float x = data.at("X");
	float y = data.at("Y");
	float w = data.at("W");
	float h = data.at("H");

	setPosition({ x, y });
	setSize({ w,h });
	bodyType = b2BodyType::b2_staticBody;
}

Tree::~Tree()
{
}

void Tree::CreatePhysics(b2World* world)
{
	// Position the collider
	setSize(getSize() / 20.0f);
	setSize({ getSize().x, getSize().y / 10.0f });
	setPosition({ getPosition().x, getPosition().y - getSize().x });
	InitPhysics(world, BodyType, density, friction);
	//Reset the body size
	setPosition({ getPosition().x, getPosition().y + getSize().x });
	setSize({ getSize().x, getSize().y * 10.0f });
	setSize(getSize() * 20.0f);
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
	glm::vec2 pos = { this->position.x, this->position.y - (this->size.y / 2) + (size.y / 10) };
	leafTransp = 1.0f;
	// Turn transparent if player is underneath
	if (GameSettings::currentInstance->I_player.getPosition().y > pos.y - (size.y / 2) && GameSettings::currentInstance->I_player.getPosition().y < pos.y + (size.y / 4))
		if(GameSettings::currentInstance->I_player.getPosition().x > pos.x - (size.x / 2)&& GameSettings::currentInstance->I_player.getPosition().x < pos.x + (size.x / 2))
			leafTransp = 0.5f;

	leafColour = { 200,100,200 };

	int layeroffset = 0;
	if (GameSettings::currentInstance->I_player.getPosition().y < this->position.y)
		layeroffset = 1;

	renderer.RenderSpriteLighting(this->Stump, this->StumpNormal, pos, this->size, this->rotation, this->transparency, this->renderLayer + layeroffset, this->colour, flipSprite);
	renderer.RenderSpriteLighting(this->Leaves, this->LeavesNormal, pos, this->size, this->rotation, leafTransp, this->renderLayer + layeroffset, leafColour, flipSprite);
	//renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}

std::shared_ptr<Item> Tree::getSharedPointer()
{
	auto sharedItem = std::make_shared<Tree>(*this); // make shared Item
	return sharedItem;
}
