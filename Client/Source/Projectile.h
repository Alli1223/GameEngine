#pragma once
#include "GameObject.h"
#include "Timer.h"
class Projectile : public NetworkObject
{
public:
	Projectile();
	Projectile(b2World* physicsWorld, glm::vec2 startPosition, b2Vec2 velocity);
	~Projectile();

	std::shared_ptr<Projectile> getSharedPointer();
	std::string getType() { return type; }

	json GetJson();

	void startContact();

	void NetworkUpdate(json data);

	void Update();
	//void Render(GL_Renderer& renderer);

	bool isTraveling = false;
	Timer experationTimer;

	b2Vec2 direction;
	float AliveTime = 20; // Time till the sprite gets deleted in ms

protected:
	int damage = 2;
	std::string type = "Projectile";

	std::shared_ptr<Projectile> thisPointer = nullptr;
};

struct Arrow : public Projectile
{


protected:
	std::string type = "Arrow";
	std::shared_ptr<Arrow> thisPointer = nullptr;
};