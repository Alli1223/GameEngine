#include "stdafx.h"
#include "GameSettings.h"

Instance* GameSettings::currentInstance = nullptr;
glm::ivec2 GameSettings::windowSize = { 1920,1080 };

GameSettings::GameSettings()
{
	//Calculate and correct fps
}


GameSettings::~GameSettings()
{
}

glm::vec2 GameSettings::getScreenResolution()
{
	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

		int should_be_zero = SDL_GetCurrentDisplayMode(i, &currentDisplay);

		if (should_be_zero != 0)
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

		else
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, currentDisplay.w, currentDisplay.h, currentDisplay.refresh_rate);
		break;
	}
	WINDOW_HEIGHT = currentDisplay.h;
	WINDOW_WIDTH = currentDisplay.w;
	return { WINDOW_WIDTH, WINDOW_HEIGHT };
}

void GameSettings::CalculateFramesPerSecond()
{
	
	avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	std::cout << avgFPS << std::endl;
	countedFrames++;

}


//TODO: Create a mapdata json file for singleplayer
//void GameSettings::savePlayerSettings(Player& player)
//{
//	
//	json playerData = player.getPlayerJson();
//
//	playerSave.open(playerSavePath);
//	playerSave << playerData.dump();
//	std::cout << "Saved Player settings." << std::endl;
//	playerSave.close();
//}

TileSheet GameSettings::getTileSetFromID(int ID)
{
	for (auto& tileSet : Tiled_TileSheets)
	{
		if (tileSet.startingGID >= ID && ID < tileSet.startingGID + tileSet.tilecount)
		{
			return tileSet;
		}
	}
}




Player GameSettings::getPlayerFromSave()
{
	Player existingPlayer;
	std::string line;
	std::ifstream readPlayerSave(playerSavePath);
	try
	{

		if (readPlayerSave.is_open())
		{
			while (std::getline(readPlayerSave, line))
			{
				//saveData = line;
				json jsonData = json::parse(line.begin(), line.end());;
				json playerData = jsonData.at("PlayerData");

				// Player movement
				int x = playerData.at("X").get<int>();
				int y = playerData.at("Y").get<int>();
				int rotation = playerData.at("rotation").get<int>();
				std::string name = playerData.at("name").get<std::string>();
				bool isMoving = playerData.at("isMoving").get<bool>();

				// Player clothes

				// ints for converting the json enums
				int headWear;
				int bodyWear;
				int legWear;
				int EarType;
				int EyeType;
				int gender;

				// Check to see if the data is there
				if (playerData.count("headWear") > 0)
				{
					headWear = playerData.at("headWear").get<int>();
				}
				if (playerData.count("bodyWear") > 0)
				{
					bodyWear = playerData.at("bodyWear").get<int>();
				}
				if (playerData.count("bodyWear") > 0)
				{
					legWear = playerData.at("legWear").get<int>();
				}
				if (playerData.count("eyeType") > 0)
				{
					EyeType = playerData.at("eyeType").get<int>();
				}
				if (playerData.count("earType") > 0)
				{
					EarType = playerData.at("earType").get<int>();
				}
				if (playerData.count("gender") > 0)
				{
					gender = playerData.at("gender").get<int>();
				}
				json hairColour = playerData.at("hairColour");
				int hr = hairColour.at("r").get<int>();
				int hg = hairColour.at("g").get<int>();
				int hb = hairColour.at("b").get<int>();
				json eyeColour = playerData.at("eyeColour");
				int er = eyeColour.at("r").get<int>();
				int eg = eyeColour.at("g").get<int>();
				int eb = eyeColour.at("b").get<int>();
				json upperClothesColour = playerData.at("upperClothesColour");
				int jr = upperClothesColour.at("r").get<int>();
				int jg = upperClothesColour.at("g").get<int>();
				int jb = upperClothesColour.at("b").get<int>();
				json legsColour = playerData.at("legColour");
				int lr = legsColour.at("r").get<int>();
				int lg = legsColour.at("g").get<int>();
				int lb = legsColour.at("b").get<int>();
				json bodyColour = playerData.at("bodyColour");
				int br = bodyColour.at("r").get<int>();
				int bg = bodyColour.at("g").get<int>();
				int bb = bodyColour.at("b").get<int>();
				existingPlayer.setEyeColour(er, eg, eb);
				existingPlayer.setHairColour(hr, hg, hb);
				existingPlayer.setJacketColour(br, bg, bb);
				existingPlayer.setJeansColour(lr, lg, lb);
				existingPlayer.setBodyColour(br, bg, bb);

				existingPlayer.body.gender = (Player::Body::Gender)gender;
				existingPlayer.body.earType = (Player::Body::EarType)EarType;
				existingPlayer.body.eyeType = (Player::Body::EyeType)EyeType;
				existingPlayer.CharacterClothes.hat = (Player::Clothing::HeadWear)headWear;
				existingPlayer.CharacterClothes.body = (Player::Clothing::BodyWear)bodyWear;
				existingPlayer.CharacterClothes.leg = (Player::Clothing::LegWear)legWear;
				existingPlayer.setPlayerMoving(isMoving);

			}

			readPlayerSave.close();
		}
	}
	catch (std::exception e)
	{
		printf("Error getting saved player %s", e.what());
	}
	return existingPlayer;
}