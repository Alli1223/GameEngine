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
	if (isSelected)
	{
		int mX = 0, mY = 0;
		if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_RIGHT) && path.size() == 0)
		{

			mX = (mX + I_renderer->camera.getX() + (I_renderer->currentInstanceCellSize / 2)) / I_renderer->currentInstanceCellSize;
			mY = (mY + I_renderer->camera.getY() + (I_renderer->currentInstanceCellSize / 2)) / I_renderer->currentInstanceCellSize;

			path = pathfinder->findPathThread(tiles, getPosition() / (float)I_renderer->currentInstanceCellSize, { mX,mY });
			this->s_action = ShopActions::movingToPostion;
		}
		else
		{
			if (s_action == ShopActions::browsing && path.size() > 0)
			{
				this->s_action = ShopActions::idle;
				path.erase(path.begin(), path.end());
			}
		}
	}
	else
	{
		this->s_action = ShopActions::browsing;
	}
	if (path.size() == 0)
	{
		setPlayerMoving(false);
		switch (s_action)
		{
			// Choose random spot in room to walk to
		case ShopActions::browsing:

			path = pathfinder->findPathThread(tiles, getPosition() / 100.0f, { rand() % tiles.size(), rand() % tiles[0].size() });
			break;

			// Walk to the exit
		case ShopActions::exiting:
			break;
		case ShopActions::idle:
			
			break;
		}
	}
	else
		UpdatePathPosition();

}

