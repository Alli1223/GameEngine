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

	lerp_x = 10.0f;
	lerp_y = 10.0f;
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
	//getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	//vec2 pos = getPosition();// { getBody()->GetPosition().x, getBody()->GetPosition().y };
	//float dist = GetDistance(pos, newPos);
	//
	//float lerp_x = getPosition().x + (newPos.x - getPosition().x) * 0.3f;
	//float lerp_y = getPosition().y + (newPos.y - getPosition().y) * 0.3f;
	//
	//lerp_x = 10.0f;
	//lerp_y = 10.0f;
	////if (dist > 200.0f)
	//{
	//	std::cout << "Distance to destination " << playerName << " is: " << dist << std::endl;
	//	//setPosition(newPos);
	//	//getBody()->SetTransform(b2Vec2(newPos.x, newPos.y), getBody()->GetAngle());
	//	getPosition();
	//}
	//if (dist > 1000.0f)
	//{
	//	if (newPos.x > pos.x)
	//		getBody()->ApplyForceToCenter(b2Vec2(+lerp_x, 0.0f), true);
	//	if (newPos.x < pos.x)
	//		getBody()->ApplyForceToCenter(b2Vec2(-lerp_x, 0.0f), true);
	//	if (newPos.y > pos.y)
	//		getBody()->ApplyForceToCenter(b2Vec2(0.0f, +lerp_y), true);
	//	if (newPos.y < pos.y)
	//		getBody()->ApplyForceToCenter(b2Vec2(0.0f, -lerp_y), true);
	//}
}
