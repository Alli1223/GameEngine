#include "stdafx.h"
#include "PlayerShop.h"


PlayerShop::PlayerShop()
{
}

PlayerShop::PlayerShop(b2World* physicsWorld)
{
	//Room shopfloor;
	//auto Shopfloor = std::make_shared<Room>(shopfloor);
	this->setSize(500, 500);
	this->setPosition(500, -500);
	chestTest.setPosition(100, 200);
	chestTest.setSize(50, 50);

	exit.setPosition(500,800);
	exit.setSize(50, 50);
	entrance.setPosition({ getPosition().x - 30, getPosition().y  + 200});
	entrance.setSize(50, 50);
	spawn.setPosition(500, 700);

	//this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Buildings\\PotionShop.png");
	//this->NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Buildings\\PotionShop_normal.png");
	spritePath = "Resources\\Sprites\\Buildings\\PotionShop.png";
	spritePath_normal = "Resources\\Sprites\\Buildings\\PotionShop_normal.png";
	this->renderLayer = 3;
	BuildingType = "PlayerShop";
	//Room room;
	//Shopfloor = std::make_shared<Room>(room);
}
std::shared_ptr<Building> PlayerShop::getSharedPointer()
{
	if (thisuildingPointer == nullptr)
	{
		thisuildingPointer = std::make_shared<PlayerShop>(*this);
		return thisuildingPointer;
	}
	else
		return thisuildingPointer;
}

// Create the shop from a json file
PlayerShop::PlayerShop(b2World* physicsWorld, json jsonData)
{
	BuildingType = "PlayerShop";
	// Shop size and position
	float X = jsonData.at("X").get<float>();
	float Y = jsonData.at("Y").get<float>();
	float width = jsonData.at("Width");
	float height = jsonData.at("Height");
	setPosition(X, Y);
	setSize(width, height);
	int tileWidth = jsonData.at("TileWidth").get<int>();
	int tileHeight = jsonData.at("TileHeight").get<int>();

	// Shop entrance exit and spawn positions
	// Entrance and Exit
	float entranceX = jsonData.at("EntranceX");
	float entranceY = jsonData.at("EntranceY");
	float exitX = jsonData.at("ExitX");
	float exitY = jsonData.at("ExitY");
	float spawnX = jsonData.at("SpawnX");
	float spawnY = jsonData.at("SpawnY");

	entrance.setPosition(entranceX, entranceY);
	entrance.setSize(50, 50);
	exit.setPosition(exitX, exitY);
	exit.setSize(50, 50);
	spawn.setPosition(spawnX, spawnY);


	
	//// Tile size
	//int tileSize = jsonData.at("TileSize");
	//this->setTileSize(tileSize);
	//// Get the tiles from file and assign them
	//json tileData = jsonData.at("TileData");
	//for (auto& tile : tileData)
	//{
	//	Cell newCell(physicsWorld, tile);
	//	newCell.setSize(tileSize, tileSize);
	//	tiles[newCell.getX()][newCell.getY()] = std::make_shared<Cell>(newCell);
	//}
	//init = true;	// set so the tiles arent created again
	//
	//
	//json displayShelfs = jsonData.at("DisplayShelfs");
	//
	//// Loop through display shelves
	//for (auto& shelf : displayShelfs)
	//{
	//	// Create and place shelf
	//	ShopDisplayShelf shelfObj;
	//	float X_shelf = shelf.at("X");
	//	float Y_shelf = shelf.at("Y");
	//	float width_s = shelf.at("Width");
	//	float height_s = shelf.at("Height");
	//	shelfObj.setPosition(X_shelf, Y_shelf);
	//	shelfObj.setSize(width_s, height_s);
	//
	//	// Create its items
	//	json items = shelf.at("Items");
	//	for (auto& item : items)
	//	{
	//		float X_item = item.at("X");
	//		float y_item = item.at("Y");
	//		std::string type = item.at("Type");
	//		
	//		if (type == "Fish")
	//		{
	//			Fish fish;
	//			fish.setPosition(X_item, y_item);
	//			shelfObj.AddItem(fish.getSharedPointer());
	//		}
	//	}
	//	shopDisplays.push_back(shelfObj.getShelfPointer());	// Add the shelf
	//
	//}
	//this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Buildings\\PotionShop.png");
	//this->NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Buildings\\PotionShop_normal.png");
	spritePath = "Resources\\Sprites\\Buildings\\PotionShop.png";
	spritePath_normal = "Resources\\Sprites\\Buildings\\PotionShop_normal.png";
}


bool PlayerShop::AddShopDisplay(std::shared_ptr<ShopDisplayShelf>& counter)
{
	//if (counter->getX() + counter->getSize().x <= tiles.size() && counter->getY() + counter->getSize().y <= tiles[0].size() && counter->getX() >= 0 && counter->getY() >= 0) // bounds checking
	//{
	//	if (tiles[counter->getX()][counter->getY()]->isWalkable)		// only place on walkable cells
	//	{
	//
	//		for (int x = 0; x < counter->getSize().x; x++)			// Set as not walkable
	//			for (int y = 0; y < counter->getSize().y; y++)
	//			{
	//				tiles[counter->getX() + x][counter->getY() + y]->isWalkable = false;
	//			}
	//		counter->setPosition(counter->getPosition() * tiles[0][0]->getSize());	// Reposition the counter
	//		counter->setSize(counter->getSize() * tiles[0][0]->getSize());		//Resize the counter
	//
	//		shopDisplays.push_back(counter);
	//		return true;
	//	}
	//}
	return false;
}
// Add a customer by a pointer referernce
void PlayerShop::AddCustomer(std::shared_ptr<NPC> npc)
{
	customers.push_back(npc);
}

// Remove a customer with a specified ID
void PlayerShop::RemoveCustomer(int ID)
{
	for (int i = 0; i < customers.size(); i++)
		if (customers[i]->getID() == ID)
			customers.erase(customers.begin() + i);
	
}

void PlayerShop::OnEnter()
{
	
	//GameSettings::currentInstance = Shopfloor->getInstance();
}

// Render the shop items
void PlayerShop::Render(GL_Renderer& renderer)
{
	// Initalise the sprites
	if (!initalised)
	{
		chestTest.setPosition(500, 500);
		InitSprite();
		SunflowerSeeds ss;
		for (int i = 0; i < 5; i++)
			chestTest.inventory.add(ss.getSharedPointer());
	}
	if (!hasPhysics)
	{
		setSize({ getSize().x / 1.5, getSize().y / 2.2f });
		//InitPhysics(renderer.p_World.get(), b2BodyType::b2_staticBody, 10.0f, 0.0f);
		setSize({ getSize().x * 1.5, getSize().y * 2.2f });
	}

	// Render the inside or outside

	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);

	outsideLantern.setPosition({ this->getPosition().x, this->getPosition().y + size.y / 3 });
	outsideLantern.lightType = LightSource::LightType::streetLight;
	outsideLantern.renderLayer = renderLayer;
	outsideLantern.Render(renderer);
	entrance.renderLayer = 4;
	entrance.Sprite = ResourceManager::GetAtlasTexture("roguelike", 600);
	entrance.Render(renderer);
}
	


void PlayerShop::Update(World & world)
{
	// Update the customers
	for (auto& customer : customers)
	{
		customer->Update(world);
	}
}

void PlayerShop::RenderInterior(GL_Renderer& renderer)
{
;
	
}

PlayerShop::~PlayerShop()
{
}
