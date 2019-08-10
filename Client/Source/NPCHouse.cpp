#include "stdafx.h"
#include "NPCHouse.h"


NPCHouse::NPCHouse()
{
	// redo this
	HouseID = "NPCHouse_" + std::to_string(SDL_GetTicks());
	// Ground
	//this->GroundFloorBackground = ResourceManager::LoadTexture(modularHouseDirectory + "Ground\\Ground-Foreground-2.png");
	this->GroundFloorDecoration = ResourceManager::LoadTexture(modularHouseDirectory + "Ground\\Ground-Foreground-2.png");
	//this->GroundFloorWindows = ResourceManager::LoadTexture(modularHouseDirectory + "Windows\\Ground-Windows-1.png");
	//this->GroundFloorDoor = ResourceManager::LoadTexture(modularHouseDirectory + "Doors\\Door-2.png");
	// Roof
	//this->RoofBackground = ResourceManager::LoadTexture(modularHouseDirectory + "Roof\\Roof-Background-2.png");
	this->RoofDecoration = ResourceManager::LoadTexture(modularHouseDirectory + "Roof\\Roof-ForeGround-2.png");
	// 
	this->NormalMap = ResourceManager::LoadTexture(modularHouseDirectory + "Ground\\Ground-Background.png");

	this->renderLayer = 3;
	this->setSize(300, 300);


	entrance.setSize(50, 50);
	exit.setSize(50, 50);
	entrance.renderLayer = 4;
	exit.renderLayer = 4;
}
std::shared_ptr<Building> NPCHouse::getSharedPointer()
{
	return std::make_shared<NPCHouse>(*this);
}

NPCHouse::~NPCHouse()
{
}

void NPCHouse::CreateOccupants(int number)
{
	// Create villagers
	for (int i = 0; i < number; i++)
	{
		Villager newOccupant;

		newOccupant.setPosition(((rand() % 10000) - 500), ((rand() % 10000) - 500) );
		newOccupant.GenerateVillager();

		occupants.push_back(newOccupant.getSharedPointer());
	}
}

void NPCHouse::RemoveOccupant(int id)
{
	for (int i = 0; i < occupants.size(); i++)
		if (occupants[i]->getID() == id)
			occupants.erase(occupants.begin() + i);
	
}

void NPCHouse::RenderInterior(GL_Renderer& renderer)
{
	//if (!init)
	//	InitBuilding();
	// Render floor
	//for (int x = 0; x < tiles.size(); x++)
	//	for (int y = 0; y < tiles[x].size(); y++)
	//	{
	//		tiles[x][y]->Render(renderer);
	//	}


	exit.Sprite = ResourceManager::GetAtlasTexture("roguelike", 600);
	exit.Render(renderer);

}

void NPCHouse::Render(GL_Renderer& renderer)
{
	// Init physics
	if (!hasPhysics)
	{
		// Resize for setting the collsion border
		setSize({ getSize().x, getSize().y / 1.8f });
		//InitPhysics(renderer.p_World.get(), b2BodyType::b2_staticBody, 10.0f, 0.0f);
		setSize({ getSize().x, getSize().y * 1.8f });
		// Set entrance and exits
		entrance.setPosition({ getPosition().x - 30, getPosition().y + 100 });
		spawn.setPosition(500, 650);
		exit.setPosition(500, 850);
	}

	// Render the occupants
	for (auto& occupant : occupants)
	{
		occupant->Render(renderer);
	}




	entrance.Sprite = ResourceManager::GetAtlasTexture("roguelike", 600);
	entrance.Render(renderer);
	// Render house layers
	if (!hasFirstFloor)
	{
		glm::vec2 sectionSize = { size.x, size.y / 2.0f };
		glm::vec2 groundPos = { position.x, position.y + (sectionSize.y / 2.0f) };
		glm::vec2 roofPos = { position.x, position.y - (sectionSize.y / 2.0f) };

		//Ground
		if (this->GroundFloorBackground.Width > 0 && this->GroundFloorBackground.Height > 0)
			renderer.RenderSpriteLighting(this->GroundFloorBackground, this->NormalMap, groundPos, sectionSize, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
		if (this->GroundFloorDecoration.Width > 0 && this->GroundFloorDecoration.Height > 0)
			renderer.RenderSpriteLighting(this->GroundFloorDecoration, this->NormalMap, groundPos, sectionSize, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
		if (this->GroundFloorWindows.Width > 0 && this->GroundFloorWindows.Height > 0)
			renderer.RenderSpriteLighting(this->GroundFloorWindows, this->NormalMap, groundPos, sectionSize, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
		if (this->GroundFloorDoor.Width > 0 && this->GroundFloorDoor.Height > 0)
			renderer.RenderSpriteLighting(this->GroundFloorDoor, this->NormalMap, groundPos, sectionSize, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
		//Roof
		if (this->RoofBackground.Width > 0 && this->RoofBackground.Height > 0)
			renderer.RenderSpriteLighting(this->RoofBackground, this->NormalMap, roofPos, sectionSize, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
		if (this->RoofDecoration.Width > 0 && this->RoofDecoration.Height > 0)
			renderer.RenderSpriteLighting(this->RoofDecoration, this->NormalMap, roofPos, sectionSize, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
	}


}
