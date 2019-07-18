#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(GL_Renderer& renderer, b2World* physicsWorld, glm::vec2 startPosition, b2Vec2 velocity) : collisionInentity(CollisionIdentifier::CollisionEntityTypes::projectile)
{
	// set position before initilsing physics
	this->setPosition(startPosition);
	this->setSize(25, 25);
	this->renderLayer = 3;
	collisionInentity.object = this;
	InitPhysics(physicsWorld, collisionInentity, b2BodyType::b2_dynamicBody, 1.0f, 100.3f);

	// set as bullet so it cant travel through objects at fast speeds
	this->getBody()->SetBullet(true);



	getBody()->ApplyForceToCenter(velocity, true);
	//getBody()->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), b2Vec2(getPosition().x, getPosition().y), true);
	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 1015);
	experationTimer.start();
}

Projectile::Projectile() : collisionInentity(CollisionIdentifier::CollisionEntityTypes::projectile)
{
	collisionInentity.object = this;
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

void Projectile::startContact()
{
	AliveTime = 0;
}


