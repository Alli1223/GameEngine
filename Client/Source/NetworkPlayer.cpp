#include "stdafx.h"
#include "Networkplayer.h"


NetworkPlayer::NetworkPlayer()
{
}


NetworkPlayer::~NetworkPlayer()
{
}

void NetworkPlayer::Update()
{
	getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	vec2 pos = getPosition();// { getBody()->GetPosition().x, getBody()->GetPosition().y };
	float dist = GetDistance(pos, lastKnownPos);

	float lerp_x = getPosition().x + (lastKnownPos.x - getPosition().x) * 0.3f;
	float lerp_y = getPosition().y + (lastKnownPos.y - getPosition().y) * 0.3f;

	lerp_x = 100.0f;
	lerp_y = 100.0f;
	if (lastKnownPos.x > pos.x + 11.0f)
		getBody()->ApplyForceToCenter(b2Vec2(+lerp_x, 0.0f), true);
	if (lastKnownPos.x < pos.x - 11.0f)
		getBody()->ApplyForceToCenter(b2Vec2(-lerp_x, 0.0f), true);
	if (lastKnownPos.y > pos.y + 11.0f)
		getBody()->ApplyForceToCenter(b2Vec2(0.0f, +lerp_y), true);
	if (lastKnownPos.y < pos.y - 11.0f)
		getBody()->ApplyForceToCenter(b2Vec2(0.0f, -lerp_y), true);
}

void NetworkPlayer::Move(glm::vec2 newPos)
{
	lastKnownPos = newPos;
	
	
	vec2 pos = getPosition();// { getBody()->GetPosition().x, getBody()->GetPosition().y };
	if ((glm::ivec2)pos != (glm::ivec2)newPos)
	{
		getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		float dist = GetDistance(pos, newPos);

		float lerp_x = getPosition().x + (newPos.x - getPosition().x);
		float lerp_y = getPosition().y + (newPos.y - getPosition().y);


		lerp_x = getSpeed() * (dist * 0.01f);
		lerp_y = getSpeed() * (dist * 0.01f);

		std::cout << dist << std::endl;
		//if (dist > 1000000.0f)
		{
			if (newPos.x > pos.x + getSpeed())
				getBody()->ApplyForceToCenter(b2Vec2(+lerp_x, 0.0f), true);
			if (newPos.x < pos.x - getSpeed())
				getBody()->ApplyForceToCenter(b2Vec2(-lerp_x, 0.0f), true);
			if (newPos.y > pos.y + getSpeed())
				getBody()->ApplyForceToCenter(b2Vec2(0.0f, +lerp_y), true);
			if (newPos.y < pos.y - getSpeed())
				getBody()->ApplyForceToCenter(b2Vec2(0.0f, -lerp_y), true);
		}
	}
}
