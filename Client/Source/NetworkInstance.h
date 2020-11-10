#pragma once
#include "Instance.h"
#include "GameSettings.h"
#include "NetworkManager.h"
#include "Enemy.h"
class NetworkInstance : public Instance
{
public:
	NetworkInstance::NetworkInstance();
	NetworkInstance::~NetworkInstance();

	std::map<std::pair<int, int>, std::shared_ptr<Cell>> level;

	//! When player enters instance
	void onEnter(Player& player);

	//! Instance setup
	void InstanceSetup(Player& player);

	//! When player exits instace
	void onExit(Player& player);

	//! Create a cell at a location
	void CreateCell(vec2 pos);

	std::shared_ptr<Cell> GetCell(vec2 pos);
	std::shared_ptr<Cell> GetCell(float x, float y);

	//! Add cell to update list
	void UpdateCell(std::shared_ptr<Cell> cell);

	//! Render
	void Render(GL_Renderer& Renderer);

	//! Update
	void Update();

	void NetworkUpdate();

	NetworkManager* network;

	Timer networkUpdateTimer;

private:
	//! Update rate to server in ms
	unsigned int updateRate = 20;
	//! default Cellsize
	int cellSize = 100;
	
	std::string mapData;

	//! Procedural generation instance
	ProceduralTerrain procGen;
};

