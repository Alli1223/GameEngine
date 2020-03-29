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
	
	

protected:
	std::string SpriteDirctory = "Resources\\External\\";
	glm::vec2 lastKnownPos;

	bool isMoving = false;
};

class Slime : public Enemy
{
public:
	Slime::Slime();
	Animation slimeAnim;

	void Render(GL_Renderer& renderer);
private:

};
