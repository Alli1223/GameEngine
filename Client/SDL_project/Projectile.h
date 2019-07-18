#pragma once
#include "GameObject.h"
#include "Timer.h"
class Projectile : public GameObject
{
public:
	Projectile();
	Projectile(GL_Renderer& renderer, b2World* physicsWorld, glm::vec2 startPosition, b2Vec2 velocity);
	~Projectile();

	std::shared_ptr<Projectile> getSharedPointer();
	std::shared_ptr<Projectile> thisPointer = nullptr;
	CollisionIdentifier collisionInentity;

	void startContact();
	//void Render(GL_Renderer& renderer);

	bool isTraveling = false;
	Timer experationTimer;

	float AliveTime = 1000; // Time till the sprite gets deleted in ms

protected:
	int damage = 2;
};
