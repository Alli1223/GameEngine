#pragma once
#include "NPC.h"
class Enemy : public NetworkObject
{
public:
	Enemy();
	Enemy(int ID);
	void NetworkUpdate(json data);

	virtual void Render(GL_Renderer& renderer);
	void Update();
	void UpdatePosition();
	void Move(glm::vec2 newPos);
	
	std::shared_ptr<Enemy> getSharedPointer();
	

protected:
	std::string SpriteDirctory = "Resources\\External\\";
	glm::vec2 lastKnownPos;
	std::shared_ptr<Enemy> thisPointer = nullptr;
	bool isMoving = false;
	int health = 100;
	std::string type = "null";
};

class Slime : public Enemy
{
public:
	Slime::Slime();
	Slime::Slime(int ID);
	Animation slimeAnim;
	std::shared_ptr<Slime> getSharedPointer();
	void Render(GL_Renderer& renderer);
private:
	std::shared_ptr<Slime> thisPointer = nullptr;
	std::string type = "Slime";
};
