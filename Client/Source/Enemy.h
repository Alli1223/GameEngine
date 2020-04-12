#pragma once
#include "NPC.h"
class Enemy : public GameObject
{
public:
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
};

class Slime : public Enemy
{
public:
	Slime::Slime();
	Animation slimeAnim;

	std::shared_ptr<Slime> getSharedPointer();

	void Render(GL_Renderer& renderer);
private:
	std::shared_ptr<Slime> thisPointer = nullptr;
	//float speed = 0.5f;

};
