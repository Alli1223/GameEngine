#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(b2World* physicsWorld, glm::vec2 startPosition, b2Vec2 velocity) 
{
	direction = velocity;
	density = 1.0f;
	friction = 10.0f;
	// set position before initilsing physics
	this->setPosition(startPosition);
	this->setSize(25, 25);
	this->renderLayer = 3;

	InitPhysics(physicsWorld, b2BodyType::b2_dynamicBody, 1.0f, 100.3f);

	// set as bullet so it cant travel through objects at fast speeds
	this->getBody()->SetBullet(true);

	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 1015);

	getBody()->ApplyForceToCenter(velocity, true);
	//getBody()->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), b2Vec2(getPosition().x, getPosition().y), true);
	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 1015);
	experationTimer.start();
}

Projectile::Projectile()
{
	//this->getBody()->SetBullet(true);

	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 1015);
}
Projectile::~Projectile()
{
}

std::shared_ptr<Projectile> Projectile::getSharedPointer()
{
	if (thisPointer != nullptr)
		return thisPointer;
	else
		thisPointer = std::make_shared<Projectile>(*this);


	return thisPointer;
}

json Projectile::GetJson()
{
	json Item;
	Item["Type"] = type;
	Item["X"] = this->getPosition().x;
	Item["Y"] = this->getPosition().y;
	Item["DX"] = this->direction.x;
	Item["DY"] = this->direction.y;
	return Item;
}

void Projectile::startContact()
{
	AliveTime = 0;
}

void Projectile::NetworkUpdate(json data)
{
	float x = data.at("X").get<float>();
	float y = data.at("Y").get<float>();
	int rotation = data.at("rotation").get<int>();
	setBodyPosition({ x,y });
}

void Projectile::Update()
{
}


