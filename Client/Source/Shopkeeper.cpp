#include "stdafx.h"
#include "Shopkeeper.h"

Shopkeeper::Shopkeeper()
{
	characterType = "Shopkeeper";
	renderLayer = 3;
}

Shopkeeper::~Shopkeeper()
{
}

std::shared_ptr<NPC> Shopkeeper::getSharedPointer()
{
	if (thisptr == nullptr)
	{
		auto sharedNPCptr = std::make_shared<Shopkeeper>(*this);
		thisptr = sharedNPCptr;
		return std::shared_ptr<NPC>(thisptr);
	}
	else
	{
		return thisptr;
	}
}

void Shopkeeper::Update()
{
	if (path.size() == 0)
	{
		switch (s_action)
		{
			// Choose random spot in room to walk to
		case ShopActions::browsing:
			path = pathfinder->findPathThread(tiles, getPosition() / 100.0f, { rand() % tiles.size(), rand() % tiles[0].size() });
			//this->path = pathfinder->findPathThread(world, this->getPosition() / (float)world.playerShop.getTileSize(), { rand() % 5, rand() % 5 }, isInShop);
			break;
			// Walk to the exit
		case ShopActions::exiting:
			//this->path = pathfinder->findPathThread(world, this->getPosition() / (float)world.getCellSize(), world.playerShop.entrance.getPosition() / (float)world.getCellSize(), isInShop);
			break;
		}
	}
	else
		UpdatePathPosition();
}