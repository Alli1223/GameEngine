#pragma once
#include "Instance.h"
#include "GameSettings.h"
#include "NetworkManager.h"
#include "Enemy.h"
class ServerWorld : public Instance
{
public:
	ServerWorld::ServerWorld();
	ServerWorld::~ServerWorld();

	std::map<std::pair<int, int>, std::shared_ptr<Cell>> level;

	//! When player enters instance
	void onEnter(Player& player);

	//! Instance setup
	void InstanceSetup(Player& player);

	//! When player exits instace
	void onExit(Player& player);

	//! Render
	void Render(GL_Renderer& Renderer);

	//! Update
	void Update();

	void NetworkUpdate();

	NetworkManager* network;

	Timer networkUpdateTimer;

private:
	int cellSize = 100;
	std::string mapData;
};

