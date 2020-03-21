#include "stdafx.h"
#include "Enemy.h"

Slime::Slime()
{
	slimeAnim.oscillate = true;
	slimeAnim.maxFrames = 3;

	ResourceManager::LoadAtlas("SlimeBlue", SpriteDirctory + "\\slime-blue.png", 3, 16);

	//this->Sprite = ResourceManager::GetAtlasTexture("crops", 1);
	//this->NormalMap = ResourceManager::GetAtlasTexture("crops", 1);
}

void Slime::Render(GL_Renderer& renderer)
{
	RenderAnimation(slimeAnim, "SlimeBlue");
	//this->Sprite = ResourceManager::GetAtlasTexture("Slimeblue", slimeAnim.getCurrentFrame());
}

void Enemy::NetworkUpdate(json data)
{
	// Player movement
	float x = data.at("X").get<float>();
	float y = data.at("Y").get<float>();
	int rotation = data.at("rotation").get<int>();
	bool moving = data.at("isMoving").get<bool>();

	setPosition(x, y);
	setRotation(rotation);
	this->isMoving = moving;
}

void Enemy::Update()
{
}

void Enemy::UpdatePosition()
{
	Move(lastKnownPos);
}

void Enemy::Move(glm::vec2 newPos)
{
	lastKnownPos = newPos;
	getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

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
