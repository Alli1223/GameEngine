#pragma once
#include "NetworkPlayer.h"
#include "CollisionListener.h"
class Instance
{
public:
	//! Constructor
	Instance();
	//! Deconstructor
	~Instance();

	//! When player enters instance
	virtual void onEnter(Player& player);

	//! When player exits instace
	virtual void onExit(Player& player);

	//! Physics instance
	std::unique_ptr<b2World> I_Physics;

	//! Render
	virtual void Render(GL_Renderer& Renderer);

	//! Update
	virtual void Update();

	//! Player for instance
	Player* I_player = nullptr;

	//! List of players in instance
	std::vector<NetworkPlayer> networkPlayers;

};

