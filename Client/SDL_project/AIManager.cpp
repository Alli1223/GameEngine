#include "stdafx.h"
#include "AIManager.h"


AIManager::AIManager()
{
}


AIManager::~AIManager()
{
}


void AIManager::Update(SDL_Renderer* renderer, Camera& camera)
{
	if (NPCs.size() < 10)
	{
		CreateNPC();
	}
	for (int i = 0; i < NPCs.size(); i++)
	{
		NPCs[i].RenderPlayer(renderer, camera);
	}
}

void AIManager::CreateNPC()
{
	NPC newNPC;
	newNPC.setBodyColour(std::rand() % 255, std::rand() % 255, std::rand() % 255);
	newNPC.body.earType = NPC::Body::EarType(rand() % 8);
	newNPC.body.hairType = NPC::Body::HairType(rand() % 13);
	newNPC.body.gender = NPC::Body::Gender(rand() % 2);
	newNPC.body.eyeType = NPC::Body::EyeType(rand() % 13);

	newNPC.PlayerClothes.body = NPC::Clothing::BodyWear(rand() % 3);
	newNPC.PlayerClothes.leg = NPC::Clothing::LegWear(rand() % 3);

	newNPC.setPosition(rand() % 100, rand() % 200);
	newNPC.Move(Point(rand() % 100, rand() % 100));
	NPCs.push_back(newNPC);

}