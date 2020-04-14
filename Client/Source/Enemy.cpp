#include "stdafx.h"
#include "Enemy.h"

Slime::Slime()
{

	slimeAnim.oscillate = true;
	slimeAnim.maxFrames = 3;

	ResourceManager::LoadAtlas("SlimeBlue", SpriteDirctory + "mobs\\slime-blue.png", 3, 15);
	slimeAnim.OnAnimate();
	this->setSize(50,50);
	this->renderLayer = 3;

	//this->Sprite = ResourceManager::GetAtlasTexture("crops", 1);
	//this->NormalMap = ResourceManager::GetAtlasTexture("crops", 1);
	//setSpeed(1.0f);
	
}

std::shared_ptr<Slime> Slime::getSharedPointer()
{
	if (thisPointer != nullptr)
		return thisPointer;
	else
		thisPointer = std::make_shared<Slime>(*this);
	return thisPointer;
}

void Slime::Render(GL_Renderer& renderer)
{
	this->getBody()->SetBullet(true);
	RenderAnimation(slimeAnim, "SlimeBlue");

	if (hasPhysics)
		this->setPosition({ this->getBody()->GetPosition().x * physicsScaleUp,this->getBody()->GetPosition().y * physicsScaleUp }), fixture->SetSensor(true);
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}

void Enemy::NetworkUpdate(json data)
{
	// Player movement
	float x = data.at("X").get<float>();
	float y = data.at("Y").get<float>();
	int rotation = data.at("rotation").get<int>();
	bool moving = data.at("isMoving").get<bool>();
	//int health = data.at("health").get<int>();
	lastKnownPos = { x,y };
	//setPosition(x, y);
	setRotation(rotation);
	this->isMoving = moving;
}

void Enemy::Render(GL_Renderer& renderer)
{
	int test = 2;
}

void Enemy::Update()
{
	UpdatePosition();
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
		//setSpeed(10.0f);
		//if (dist == 1000000.0f)
		//{
		//	if (newPos.x > pos.x + getSpeed())
		//		getBody()->ApplyForceToCenter(b2Vec2(+lerp_x, 0.0f), true);
		//	if (newPos.x < pos.x - getSpeed())
		//		getBody()->ApplyForceToCenter(b2Vec2(-lerp_x, 0.0f), true);
		//	if (newPos.y > pos.y + getSpeed())
		//		getBody()->ApplyForceToCenter(b2Vec2(0.0f, +lerp_y), true);
		//	if (newPos.y < pos.y - getSpeed())
		//		getBody()->ApplyForceToCenter(b2Vec2(0.0f, -lerp_y), true);
		//}
		const b2Vec2 posL = { newPos.x * physicsScaleDown, newPos.y * physicsScaleDown };
		getBody()->SetTransform(posL, 0.0f);
	}
}

std::shared_ptr<Enemy> Enemy::getSharedPointer()
{
	if (thisPointer != nullptr)
		return thisPointer;
	else
		thisPointer = std::make_shared<Enemy>(*this);


	return thisPointer;
}
