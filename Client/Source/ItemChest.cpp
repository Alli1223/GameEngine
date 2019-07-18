#include "stdafx.h"
#include "ItemChest.h"


ItemChest::ItemChest()
{
	window.setSize(250, 500);
	window.inventoryPointer = &inventory;
	inventory.setCapacity(inventorySize);

}


ItemChest::~ItemChest()
{
}

bool ItemChest::CheckIfPressed(Camera& camera)
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
// Get distance from two points
float getDistance(glm::vec2& a, glm::vec2& b)
{
	float dx = a.x - a.y;
	float dy = b.x - b.y;

	float dist = 0.0;

	dist = pow(dx, 2) + pow(dy, 2);
	dist = sqrt(dist);

	return dist;
}
void ItemChest::Init()
{
	this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 332);
	this->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 332);
	initalised = true;
}

void ItemChest::Render(GL_Renderer& renderer)
{
	if (!initalised)
		Init();
	window.setPosition(renderer.camera.windowSize.x - (renderer.camera.windowSize.x / 4), renderer.camera.windowSize.y / 2);
	window.setPosition(renderer.camera.windowSize.x - (renderer.camera.windowSize.x / 4), renderer.camera.windowSize.y / 2);
	window.CreateItemSelection(inventory.getItemList());
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		if (CheckIfPressed(renderer.camera))
			isOpen = true;

	// Close if the player walks away
	if (getDistance(renderer.playerPosition, this->getPosition()) > distanceToClose)
		isOpen = false;

	// Render the item selection window
	if (isOpen)
		window.Render(renderer);

}
