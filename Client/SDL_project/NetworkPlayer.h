#pragma once
#include "Player.h"
class NetworkPlayer :
	public Player
{
public:
	NetworkPlayer();
	~NetworkPlayer();
	int getID() { return ID; }
	int setID(int newID) { return ID = newID; }
private:

	int ID = 0;
};

