#pragma once
#include "Tool.h"

struct Bobber : public GameObject
{
public:
	Bobber::Bobber()
	{
		this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Items\\Fishing\\bobber.png");
		this->setSize(25, 25);
		this->renderLayer = 2;
	}
	Bobber::~Bobber()
	{

	}

	void reset()
	{
		setSize(0, 0);
		isBobbing = false;
	}

	bool isBobbing = false;
	bool fishHooked = false;

	void Render(GL_Renderer& renderer)
	{
		this->setY(this->getY() + sin(SDL_GetTicks() / 500.0f) / 3.0f); // bob
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });
	}

};
class FishingRod : public Tool
{
public:

	FishingRod();
	~FishingRod();
	std::shared_ptr<Item> getSharedPointer()
	{
		auto sharedItem = std::make_shared<FishingRod>(*this); // make shared Item
		return sharedItem;
	}
	void Render(GL_Renderer& renderer, World& world);
	void Use(GL_Renderer& renderer, World& world, Player& player);
	void Stop();
	enum CastDirection
	{
		none, left, right, up, down
	} castDirection;

	Bobber bobber;

	Animation castingAnim;

	bool castingLine = false;
	bool isFishing = false;
	bool flipSprite;
	bool waitingForHook = false;

	float bobberDistance = 0;
private:
	std::string itemName = "FishingRod";

};


