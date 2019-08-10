#include "stdafx.h"
#include "LevelSaving.h"
#include "PlayerShop.h"

inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

LevelSaving::LevelSaving()
{
}


LevelSaving::~LevelSaving()
{
}

void LevelSaving::LoadWorld(World& world, Player& player)
{
	// Load player
	if (exists(playerSavePath))
	{
		std::ifstream t(playerSavePath);
		std::string jsonData((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		json data = json::parse(jsonData.begin(), jsonData.end());
		data = data.at("PlayerData");
		player = player.LoadFromJson(data);
	}
	// Load shop if file exists
	if (exists(shopSavePath)) 
	{
		std::ifstream t(shopSavePath);
		std::string jsonData((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		json data = json::parse(jsonData.begin(), jsonData.end());;
		PlayerShop shop = PlayerShop(world.I_Physics.get(), data);
		world.playerShop = std::make_shared<PlayerShop>(shop);
	}
	//if (exists(levelSavePath))
	//{
	//	std::ifstream t(levelSavePath);
	//	std::string jsonData((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	//	json data = json::parse(jsonData.begin(), jsonData.end());
	//}

}

void LevelSaving::SaveLevel(World& world)
{
	json levelData;
	json chunks;

	std::pair<int, int> pos;
	for (auto& chunjobj : world.InfiniWorld.MainLevel)
	{
		pos = { chunjobj.first.first, chunjobj.first.second };
		if (world.InfiniWorld.MainLevel[pos].tiles.size() > 0)
		{

			json chunk;
			json tiles;
			for (int x = 0; x < world.InfiniWorld.MainLevel[pos].tiles.size(); x++)
				for (int y = 0; y < world.InfiniWorld.MainLevel[pos].tiles[0].size(); y++)
					tiles.push_back(world.InfiniWorld.MainLevel[pos].tiles[x][y]->getCellData());

			chunk["Pos"] = std::to_string(pos.first) + "_" + std::to_string(pos.second);
			chunk["Tiles"] = tiles;
			chunk["ChunkSize"] = world.InfiniWorld.MainLevel[pos].getChunkSize();
			chunks.push_back(chunk);
			levelSave.open("Resources\\Data\\Chunks\\" + std::to_string(pos.first) + "_" + std::to_string(pos.second) + ".json");
			levelSave << chunk.dump();
			levelSave.close();
		}

	}
	//levelData["Chunks"] = chunks;
	//
	////levelData["Level"] = tiles;
	////levelData["CellSize"] = level.getCellSize();
	////levelData["Width"] = level.tiles.size();
	////levelData["Height"] = level.tiles[0].size();
	//levelSave.open(levelSavePath);
	//levelSave << levelData.dump();
	//std::cout << "Level Saved." << std::endl;
	//levelSave.close();

}


void LevelSaving::SaveWorld(World& world, Player& player)
{
	SaveShop(*world.playerShop);
	SaveLevel(world);
	SavePlayer(player);
	
}
void LevelSaving::SavePlayer(Player& player)
{
	json playerData = player.getPlayerJson();
	playerSave.open(playerSavePath);
	playerSave << playerData.dump();
	std::cout << "Saved Player Shop" << std::endl;
	playerSave.close();
}

void LevelSaving::SaveShop(PlayerShop playerShop)
{
	// Create the building
	json shop;

	// Position
	shop["X"] = playerShop.getX();
	shop["Y"] = playerShop.getY();
	shop["Width"] = playerShop.getSize().x;
	shop["Height"] = playerShop.getSize().y;

	// Entrance and Exit
	shop["EntranceX"] = playerShop.entrance.getX();
	shop["EntranceY"] = playerShop.entrance.getY();

	shop["ExitX"] = playerShop.exit.getX();
	shop["ExitY"] = playerShop.exit.getY();
	
	shop["SpawnX"] = playerShop.spawn.getX();
	shop["SpawnY"] = playerShop.spawn.getY();

	//shop["TileWidth"] = playerShop.tiles.size();
	//shop["TileHeight"] = playerShop.tiles[0].size();

	//shop["TileSize"] = playerShop.tiles[0][0]->getSize().x;

	///////////////////////////////////////
	/// Level DATA
	///////////////////////////////////////

	json tilesData;

	// Get the level data
	//for (int x = 0; x < playerShop.tiles.size(); x++)
	//	for (int y = 0; y < playerShop.tiles[x].size(); y++)
	//	{
	//		tilesData.push_back(playerShop.tiles[x][y]->getCellData());
	//	}
	//shop["TileData"] = tilesData;


	///////////////////////////////////////
	/// Display cabinets
	///////////////////////////////////////


	//List of display cabinets
	json displayShelfs;
	for (int i = 0; i < playerShop.shopDisplays.size(); i++)
	{
		json displayShelf;
		displayShelf["X"] = playerShop.shopDisplays[i]->getX();		// Set position and size
		displayShelf["Y"] = playerShop.shopDisplays[i]->getY();
		displayShelf["Width"] = playerShop.shopDisplays[i]->getSize().x;
		displayShelf["Height"] = playerShop.shopDisplays[i]->getSize().y;

		json items;
		for (int j = 0; j < playerShop.shopDisplays[i]->shelfInventory.getCurrentSize(); j++)
		{
			items.push_back(playerShop.shopDisplays[i]->shelfInventory.get(j)->getItemJson());
		}
		displayShelf["Items"] = items;	// add items
		displayShelfs.push_back(displayShelf);
	}

	shop["DisplayShelfs"] = displayShelfs;

	// List of items in each display cabinet

	// List of kiosks





	shopSave.open(shopSavePath);
	shopSave << shop.dump();
	std::cout << "Saved Player Shop" << std::endl;
	shopSave.close();

	//////////////////////////////////////////////////////////////////////////////
	/// PLAYER SHOP END
	//////////////////////////////////////////////////////////////////////////////
	


	// Add that to list


//levelData["Level"] = mainLevel;
//levelData["Buildings"] = buildings;
//levelSave.open(levelSavePath);
//levelSave << levelData.dump();
//std::cout << "Level Saved." << std::endl;
//levelSave.close();

}
