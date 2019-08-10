#pragma once
#include "PlayerShop.h"
#include "player.h"
#include "World.h"


class LevelSaving
{
public:
	LevelSaving();
	~LevelSaving();
	//! Load the level
	void LoadWorld(World& world, Player& player);
	// Save everything
	void SaveWorld(World& world, Player & player);
	//! Save the player
	void SavePlayer(Player & player);
	//! Save the shop
	void SaveShop(PlayerShop playerShop);
	//! Save the level
	void SaveLevel(World& world);

private:

	std::ofstream shopSave;
	std::ofstream levelSave;
	std::ofstream playerSave;

	const std::string shopSavePath = "Resources\\Data\\shop.json";
	const std::string levelSavePath = "Resources\\Data\\level.json";

	const std::string map1 = "Resources\\Data\\test.json";
	const std::string playerSavePath = "Resources\\Data\\playerData.json";
};

