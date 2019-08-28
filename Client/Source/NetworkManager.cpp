#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}
json ConvertToJson(std::string data)
{
	try {
		// Remove anything at the end of the json string that isn't suppose to be there
		int endOfJsonString = data.find_last_of("}");
		int startOfJsonString = data.find_first_of("{");
		if (startOfJsonString >= 0)
			data.erase(data.begin(), data.begin() + startOfJsonString);
		if (endOfJsonString >= 0)
			if (endOfJsonString + 1 < data.length())
				data.erase(data.begin() + endOfJsonString + 1, data.end());
		if (endOfJsonString != 0)
		{
			json jsonData = json::parse(data.begin(), data.end());
			return jsonData;
		}
		else
		{
			json empty;
			return empty;
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error Convering player data to json: " << e.what() << std::endl;
	}
}
int NetworkManager::init(std::string playerName)
{
	Connect();

	sendTCPMessage(playerName + "\n");
	setPlayerName(playerName);
	//int ID = RecieveMessage()
	std::cout << "PlayerName: " << localPlayerName << std::endl;


	//sendTCPMessage("[Init]\n");
	//std::string gameData = RecieveMessage();
	//json gameDataJson = ConvertToJson(gameData);
	//int totalPlayers = gameDataJson.at("TotalCurrentPlayers");
	return 0;
}

void NetworkManager::Connect()
{
	IPAddress = InternalIPAddress;
	socket = std::shared_ptr<tcp::socket>(new tcp::socket(io_service));
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(getServerIP()), port);
	socket->connect(endpoint);
	io_service.run();
}

//! Returns whether the player exists in the list of players
bool PlayerExists(std::vector<std::string> & playerNames, std::string playername)
{
	// Return true if theres a match
	for (int i = 0; i < playerNames.size(); i++)
	{
		if (playername == playerNames[i])
			return true;
	}
	// Return false if no player with that name exists
	return false;
}

//! main netwrok update function
void NetworkManager::NetworkUpdate(World& world, std::vector<NetworkPlayer>& players, Player& player)
{
	allPlayers = &players;
	// Interval Timer
	timebehindP += SDL_GetTicks() - lastTimeP;
	lastTimeP = SDL_GetTicks();

	// Interval Timer
	timebehindM += SDL_GetTicks() - lastTimeM;
	lastTimeM = SDL_GetTicks();

	// Update intervalTimer
	if (timebehindP >= networkPlayerUpdateInterval)
	{
		runPlayerNetworkTick = true;
		timebehindP -= networkPlayerUpdateInterval;
	}
	if (timebehindM >= networkMapUpdateInterval)
	{
		runMapNetworkTick = true;
		timebehindM -= networkMapUpdateInterval;
	}

	// Update network
	if (runPlayerNetworkTick)
	{
		runPlayerNetworkTick = false;
		ProcessPlayerLocations(world, player);
	}

	if (runMapNetworkTick)
	{
		runMapNetworkTick = false;
		//Process the map data
		//MapNetworkUpdate(level);
	}
}

bool NetworkManager::UpdateNetworkPlayer(json& data, std::string name)
{
	// Check if player already exists and update the values
	int ID = -1;
	for (int i = 0; i < allPlayers->size(); i++)
		if (allPlayers->at(i).playerName == name)
		{
			ID = i;
		}
	if (ID >= 0)
	{
		// Player movement
		float x = data.at("X").get<float>();
		float y = data.at("Y").get<float>();
		int rotation = data.at("rotation").get<int>();

		bool isMoving = data.at("isMoving").get<bool>();

		// Player clothes
		int headWear = data.at("headWear").get<int>();
		int bodyWear = data.at("bodyWear").get<int>();
		int legWear = data.at("legWear").get<int>();

		// Hair and eye colour
		json hairColour = data.at("hairColour");
		json eyeColour = data.at("eyeColour");
		int hr = hairColour.at("r").get<int>();
		int hg = hairColour.at("g").get<int>();
		int hb = hairColour.at("b").get<int>();
		int er = eyeColour.at("r").get<int>();
		int eg = eyeColour.at("g").get<int>();
		int eb = eyeColour.at("b").get<int>();

		json bodyColour = data.at("bodyColour");
		int br = bodyColour.at("r").get<int>();
		int bg = bodyColour.at("g").get<int>();
		int bb = bodyColour.at("b").get<int>();
		json legsColour = data.at("legColour");
		int lr = legsColour.at("r").get<int>();
		int lg = legsColour.at("g").get<int>();
		int lb = legsColour.at("b").get<int>();

		allPlayers->at(ID).setEyeColour(er, eg, eb);
		allPlayers->at(ID).setHairColour(hr, hg, hb);
		allPlayers->at(ID).setJacketColour(br, bg, bb);
		allPlayers->at(ID).setJeansColour(lr, lg, lb);
		allPlayers->at(ID).PlayerClothes.hat = (Player::Clothing::HeadWear)headWear;
		allPlayers->at(ID).PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
		allPlayers->at(ID).PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
		allPlayers->at(ID).setPlayerMoving(isMoving);
		//allPlayers->at(ID).setX(x);
		//allPlayers->at(ID).setY(y);
		allPlayers->at(ID).Move({ x,y });
		allPlayers->at(ID).setTargetRotation(rotation);
		return false;
	}
	// Player does not exist create them
	else
	{
		return true;
	}
}


void NetworkManager::ProcessPlayerLocations(World & world, Player & player)
{
	//Create the json to send to the server
	json playerData = player.getPlayerJson();


	sendTCPMessage("[PlayerUpdate]" + playerData.dump() + "\n");

	// process the list of players
	std::string updateData = RecieveMessage();

	try
	{
		json jsonData = ConvertToJson(updateData);
		json playerData = jsonData.at("PlayerData");

		// Loop through each player
		for (auto& player : playerData)
		{
			std::string name = player.at("name").get<std::string>();

			bool createPlayer = UpdateNetworkPlayer(player, name);
			if (createPlayer)
			{
				if (name.size() > 1 && name != localPlayerName)
				{
					otherPlayerNames.push_back(name);
					NetworkPlayer newPlayer;
					newPlayer.setSize({ 100,100 });
					newPlayer.setPosition({ player.at("X").get<float>(), player.at("Y").get<float>() });
					newPlayer.playerName = name;
					newPlayer.InitPhysics(world.I_Physics.get(), newPlayer.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
					allPlayers->push_back(newPlayer);
				}
			}
			/*
			if (name != localPlayerName && PlayerExists(otherPlayerNames, name))
			{

			}
			// Player movement
			float x = element.at("X").get<float>();
			float y = element.at("Y").get<float>();
			int rotation = element.at("rotation").get<int>();
			
			bool isMoving = element.at("isMoving").get<bool>();

			// Player clothes
			int headWear = element.at("headWear").get<int>();
			int bodyWear = element.at("bodyWear").get<int>();
			int legWear = element.at("legWear").get<int>();

			// Hair and eye colour
			json hairColour = element.at("hairColour");
			json eyeColour = element.at("eyeColour");
			int hr = hairColour.at("r").get<int>();
			int hg = hairColour.at("g").get<int>();
			int hb = hairColour.at("b").get<int>();
			int er = eyeColour.at("r").get<int>();
			int eg = eyeColour.at("g").get<int>();
			int eb = eyeColour.at("b").get<int>();

			json bodyColour = element.at("bodyColour");
			int br = bodyColour.at("r").get<int>();
			int bg = bodyColour.at("g").get<int>();
			int bb = bodyColour.at("b").get<int>();
			json legsColour = element.at("legColour");
			int lr = legsColour.at("r").get<int>();
			int lg = legsColour.at("g").get<int>();
			int lb = legsColour.at("b").get<int>();

			// IF player exists update deets
			if (PlayerExists(otherPlayerNames, name))
			{
				//Get players array number
				int val = 0;// getPlayer(name);
				val =
				allPlayers->at(val).setEyeColour(er, eg, eb);
				allPlayers->at(val).setHairColour(hr, hg, hb);
				allPlayers->at(val).setJacketColour(br, bg, bb);
				allPlayers->at(val).setJeansColour(lr, lg, lb);
				allPlayers->at(val).PlayerClothes.hat = (Player::Clothing::HeadWear)headWear;
				allPlayers->at(val).PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
				allPlayers->at(val).PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
				allPlayers->at(val).setPlayerMoving(isMoving);
				//allPlayers[val]->setX(x);
				//allPlayers[val]->setY(y);
				allPlayers->at(val).Move({ x,y });
				allPlayers->at(val).setTargetRotation(rotation);
			}
			*/
			//Create a new player

				
			
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error processing player location data: " << e.what() << std::endl;
	}
}



//! Process map network update
//Make sure the network send name is the same as the recieve
void NetworkManager::MapNetworkUpdate(Level & level)
{
	sendTCPMessage("[RequestMapUpdate]\n");
	//! What an empty map looks like
	std::string EmptyMap = "{\"MapData\":[]}\r\n";
	std::string mapData = RecieveMessage();
	if (mapData != EmptyMap)
	{
		// Remove anything at the end of the json string that isn't suppose to be there

		int endOfJsonString = mapData.find_last_of("}");
		int startOfJsonString = mapData.find_first_of("{");
		if (startOfJsonString >= 0)
			mapData.erase(mapData.begin(), mapData.begin() + startOfJsonString);
		int cellsUpdated = 0;

		try
		{
			json jsonData = json::parse(mapData.begin(), mapData.end());;
			json mapData = jsonData.at("MapData");

			// Range-based for loop to iterate through the map data
			for (auto& element : mapData)
			{

				Cell newCell;
				//newCell = level.GetCellFromJson(element);
				//level.SetCell(newCell.getX(), newCell.getY(), newCell);
				cellsUpdated++;
			}
			std::cout << "Cells Updated: " << cellsUpdated << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "Error processing map data: " << e.what() << std::endl;
		}
	}
}



//! Sends a tcp message to the socket
void NetworkManager::sendTCPMessage(std::string message)
{
	// Fill the buffer with the data from the string
	boost::array<char, 16384> buf;
	for (int i = 0; i < message.size(); i++)
	{
		buf[i] = message[i];
	}
	//Try sending the data
	try
	{
		boost::system::error_code error;
		socket->write_some(boost::asio::buffer(buf, message.size()), error);

		//std::cout << "Message sent: " << message << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::string make_string(boost::asio::streambuf & streambuf)
{
	return { boost::asio::buffers_begin(streambuf.data()),
		boost::asio::buffers_end(streambuf.data()) };
}
//! returns a string from the socket
std::string NetworkManager::RecieveMessage()
{
	//Create return messages and an instream to put the buffer data into
	std::string returnMessage;
	std::stringstream inStream;
	try
	{
		boost::array<char, 16384> buffer;
		boost::asio::streambuf read_buffer;
		//bytes_transferred = boost::asio::write(*socket, write_buffer);
		auto bytes_transferred = boost::asio::read_until(*socket, read_buffer, ("}\r\n"));

		//std::cout << "Read: " << make_string(read_buffer) << std::endl;

		return returnMessage = make_string(read_buffer);

	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return NULL;
}
