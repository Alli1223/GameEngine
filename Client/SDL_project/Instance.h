#pragma once
#include "Player.h"

class Instance
{
public:
	Instance();
	~Instance();

	void Update();

	//void Render(GL_Renderer& Renderer);

	void OnEnter(Player& player);

	void OnExit(Player& player);

	int ID;
	//! Physics instance
	std::unique_ptr<b2World> I_Physics;
	std::vector<std::shared_ptr<Player>> networkPlayers;

	Player I_Player;

	int getCellSize() { return 50; }

private:

	//NetworkManager networkManager;
};

