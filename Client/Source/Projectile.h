#pragma once
#include "GameObject.h"
#include "Timer.h"
class Projectile : public NetworkObject
{
public:
	Projectile();
	Projectile(b2World* physicsWorld, glm::vec2 startPosition, b2Vec2 velocity);
	~Projectile();

	virtual std::shared_ptr<Projectile> getSharedPointer();
	virtual std::string getType() { return type; }

	virtual json GetJson();

	virtual void startContact();

	virtual void NetworkUpdate(json data);

	virtual void Update();
	//void Render(GL_Renderer& renderer);

	bool isTraveling = false;
	Timer experationTimer;

	b2Vec2 direction;


protected:
	int damage = 2;
	std::string type = "Projectile";

	std::shared_ptr<Projectile> thisPointer = nullptr;
};

struct Arrow : public Projectile
{
	Arrow();
	json GetJson();
	Arrow(b2World* physicsWorld, glm::vec2 startPosition, b2Vec2 velocity);
	std::shared_ptr<Projectile> getSharedPointer();
	std::string getType() { return type; }

protected:
	std::string type = "Arrow";
	std::shared_ptr<Arrow> thisPointer = nullptr;
};