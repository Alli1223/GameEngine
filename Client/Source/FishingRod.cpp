#include "stdafx.h"
#include "FishingRod.h"
#include "World.h" // from forward decloration

FishingRod::FishingRod()
{
	ResourceManager::LoadAtlas("RodAnim", "Resources\\Sprites\\Items\\Fishing\\FishingRod.png", 4, 63);	// Paths normals
	this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Items\\Tools\\rod.png");
	this->icon.Background = ResourceManager::LoadTexture("Resources\\Sprites\\Items\\Tools\\rod.png");
	this->setSize(100, 100);
	castingAnim.maxFrames = 4;
	for (int i = 0; i < castingAnim.maxFrames; i++)
		castingAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("RodAnim", i));
}


FishingRod::~FishingRod()
{
}

void FishingRod::Render(GL_Renderer& renderer, World& world)
{
	// Stages
	// Bool Start cast
		// rod rotates till it reaches max
			// When reaches max start cast = false and casting = true
	// when casting spawn bobber
	// If player moves then stop

	if (isInFocus && isFishing)
	{
		if (this->getPosition() != renderer.playerPosition)
			Stop();
		this->setPosition(renderer.playerPosition);
		if (castingAnim.getCurrentFrame() == castingAnim.maxFrames - 1)
		{
			castingLine = false;
			waitingForHook = true;
			
		}
		if (castingLine)
		{
			castingAnim.OnAnimate();
			renderer.RenderSpriteLighting(castingAnim.Sprites[castingAnim.getCurrentFrame()], this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { flipSprite, false });
		}
		if (waitingForHook)
		{
			if (!bobber.isBobbing)
			{
				bobber.setPosition({ renderer.playerPosition.x + bobberDistance, renderer.playerPosition.y });
				bobber.setSize(25, 25);
				bobber.isBobbing = true;
			}
			bobber.Render(renderer);
			renderer.RenderSpriteLighting(castingAnim.Sprites[castingAnim.getCurrentFrame()], this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { flipSprite, false });
		}
	}
	else
	{
		Stop();
	}


}
void FishingRod::Stop()
{
	castingLine = false;
	isFishing = false;
	bobber.reset();
	waitingForHook = false;
	castingAnim.setCurrentFrame(0);
}

void FishingRod::Use(GL_Renderer& renderer, World& world, Player& player)
{
	switch (player.direction)
	{

	case Player::MovementDirection::right:
		castDirection = CastDirection::right;
		flipSprite = false;
		bobberDistance = 200.0f;
		break;
	case Player::MovementDirection::left:
		castDirection = CastDirection::left;
		flipSprite = true;
		bobberDistance = -200.0f;
		break;
	}

	if (world.GetCell((renderer.playerPosition.x + bobberDistance) / world.getCellSize(), (renderer.playerPosition.y / world.getCellSize()))->isWater)
	{
		castingLine = true;
		isFishing = true;
		player.playerAction = Player::PlayerActions::fishingCasting;
	}
	
}

