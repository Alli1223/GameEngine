#pragma once
#include "player.h"
class NetworkPlayer :
	public Player
{
public:
	NetworkPlayer();
	~NetworkPlayer();

	void Update();
	void Move(glm::vec2 newPos);

	int getID() { return ID; }
	int setID(int newID) { return ID = newID; }

	int AliveTime = 50;
private:
	vec2 lastKnownPos;
	int ID = 0;

};

