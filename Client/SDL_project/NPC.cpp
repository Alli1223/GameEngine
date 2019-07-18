#include "stdafx.h"
#include "NPC.h"

NPC::NPC()
{
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

