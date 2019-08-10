#include "stdafx.h"
#include "ShopDisplayShelf.h"
#include "player.h" // Able to get from forward decloration
#include "World.h" // Able to get from forward decloration

ShopDisplayShelf::ShopDisplayShelf() : window(shelfInventory)
{
	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 678);
	this->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 678);

	std::string directory = IconSpriteDirectory + "ShopDisplayShelf.png";
	this->icon.Background = ResourceManager::LoadTexture(directory.c_str());

	shelfInventory.setCapacity(10);
	//window.inventoryPointer = &shelfInventory;
	
	this->renderLayer = 3;
	// Testing code Remove when items are actually added
	for (int i = 0; i < 10; i++)
	{
		Fish fish;
		AddItem(fish.getSharedPointer());
	}
	window.setSize(200, 400);
}

ShopDisplayShelf::~ShopDisplayShelf()
{
}
std::shared_ptr<ShopDisplayShelf> ShopDisplayShelf::getShelfPointer()
{
	if (thisPointerReference != nullptr)
		return thisPointerReference;
	else
	{
		thisPointerReference = std::make_shared<ShopDisplayShelf>(*this); // make shared Item
		return thisPointerReference;
	}
}
std::shared_ptr<Item> ShopDisplayShelf::getSharedPointer()
{
	if (thisPointerReference != nullptr)
		return thisPointerReference;
	else
	{
		thisPointerReference = std::make_shared<ShopDisplayShelf>(*this); // make shared Item
		return thisPointerReference;
	}
}


// Get distance from two points
float getDistancee(glm::vec2& a, glm::vec2& b)
{
	float dx = a.x - a.y;
	float dy = b.x - b.y;

	float dist = 0.0;

	dist = pow(dx, 2) + pow(dy, 2);
	dist = sqrt(dist);

	return dist;
}
bool ShopDisplayShelf::CheckIfPressed(Camera& camera)
{
	glm::ivec2 mpos;
	SDL_GetMouseState(&mpos.x, &mpos.y);
	mpos += camera.getPosition();

	// Mosue over
	if (mpos.x > getX() - (getWidth() / 2) && mpos.x < getX() + (getWidth() / 2) && mpos.y > getY() - (getHeight() / 2) && mpos.y < getY() + (getHeight() / 2))
	{
		// Activate the button if it has been pressed
		if (SDL_GetMouseState(&mpos.x, &mpos.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
			return true;
	}
	return false;

}

void ShopDisplayShelf::Use(GL_Renderer & renderer, World & world, Player & player)
{
	// Place the item
	if (player.isInBuilding)
	{
		ivec2 mPos;
		if (SDL_GetMouseState(&mPos.x, &mPos.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			mPos += renderer.camera.getPosition();
			setSize(1, 2);
			//setPosition(mPos / (ivec2)world.playerShop->tiles[0][0]->getSize());
			// If the item has been placed remove it from inventory
			if(world.playerShop->AddShopDisplay(getShelfPointer()))
				player.inventory.removeItem(this->getSharedPointer());
		}
	}
}

void ShopDisplayShelf::Selected(GL_Renderer& renderer, World& world, Player& player)
{
	// Render an overlay
	int x, y;
	SDL_GetMouseState(&x, &y);
	glm::ivec2 m_pos = { x, y };
	glm::vec2 m_size = { 100,200 };
	m_pos += renderer.camera.getPosition();
	// get nearest tile cell
	//m_pos /= world.playerShop->getTileSize();
	//m_pos *= world.playerShop->getTileSize();
	
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, (vec2)m_pos, m_size, this->rotation, 0.5f, this->renderLayer, this->colour, flipSprite);
}

void ShopDisplayShelf::Render(GL_Renderer& renderer)
{
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);

	//window.inventoryPointer = &shelfInventory;
	//shelfInventory = *window.inventoryPointer;

	window.setPosition(renderer.camera.windowSize.x - (renderer.camera.windowSize.x / 4), renderer.camera.windowSize.y / 2);

	int spaceFromEdge = 5;
	int xOffset = (this->size.x / spaceFromEdge), yOffset = (this->size.y / spaceFromEdge);	// offset to start off so things are not on edge of table
	for (int i = 0; i < shelfInventory.getCapacity(); i++)	// Place the items in the cabinet
	{
		if (shelfInventory.getStack(i).size() > 0)
		{
			shelfInventory.get(i)->setSize(this->size / 5.0f);
			xOffset += shelfInventory.get(i)->getSize().x;
			if (xOffset + getX() >= getX() + getSize().x - (this->size.x / spaceFromEdge))
			{
				xOffset = (this->size.x / spaceFromEdge);
				yOffset += shelfInventory.get(i)->getSize().y;
				if (yOffset + getY() >= getY() + getSize().y - (this->size.y / spaceFromEdge))
				{
					break;
				}
			}
			shelfInventory.get(i)->renderLayer = renderLayer + 1;
			shelfInventory.get(i)->setPosition({ (this->position.x - (size.x / 2)) + xOffset,(this->position.y - (size.y / 2)) + yOffset });
			shelfInventory.get(i)->Render(renderer);
		}
	}

	//if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	//	shelfInventory.remove(0);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		if (CheckIfPressed(renderer.camera))
			itemsWindow = true;
	// Close if the player walks away
	if (itemsWindow)
		if (getDistancee(renderer.playerPosition + 100.0f, this->position) > distanceToCloseWindow)
			itemsWindow = false;

	if (itemsWindow)
	{
		window.isOpen = true;
		window.Render(renderer);
	}
	else
		window.isOpen = false;
}

void ShopDisplayShelf::AddItem(std::shared_ptr<Item> item)
{
	shelfInventory.add(item);
}
