#include "stdafx.h"
#include "NPC.h"

NPC::NPC()
{
	//TODO: make this reliable
	ID = rand() % 9999999;
	bodyType = b2BodyType::b2_dynamicBody;
}


NPC::~NPC()
{
}

void NPC::Move(MovementDirection direction)
{
	this->direction = direction;
	switch (direction)
	{
	default:
		getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		break;
	case MovementDirection::none:

		break;
	case MovementDirection::right_down:
		getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), +getSpeed()), true);
		break;
	case MovementDirection::right_up:
		getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), -getSpeed()), true);
		break;
	case MovementDirection::left_down:
		getBody()->ApplyForceToCenter(b2Vec2(-getSpeed(), +getSpeed()), true);
		break;
	case MovementDirection::left_up:
		getBody()->ApplyForceToCenter(b2Vec2(-getSpeed(), -getSpeed()), true);
		break;
	case MovementDirection::up:
		getBody()->ApplyForceToCenter(b2Vec2(0.0f, -getSpeed()), true);

		break;
	case MovementDirection::down:
		getBody()->ApplyForceToCenter(b2Vec2(0.0f, +getSpeed()), true);

		break;
	case MovementDirection::left:
		getBody()->ApplyForceToCenter(b2Vec2(-getSpeed(), 0.0f), true);

		break;
	case MovementDirection::right:
		getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), 0.0f), true);

		break;
	}
}

void NPC::Update(World & world)
{
}

void NPC::Update()
{
}

bool NPC::FindPath(glm::ivec2 start, glm::ivec2 end)
{
	if (tiles.size() > 0)
	{
		this->path = pathfinder->findPathThread(tiles, getPosition() / 100.0f, { rand() % tiles.size(), rand() % tiles[0].size() });

		if (path.size() > 0)
			return true;
		else
			return false;
	}
	return false;
}

std::shared_ptr<NPC> NPC::getSharedPointer()
{
	if (thisptr == nullptr)
	{
		auto sharedNPCptr = std::make_shared<NPC>(*this);
		thisptr = sharedNPCptr;
		return std::shared_ptr<NPC>(thisptr);
	}
	else
	{
		return thisptr;
	}

}

