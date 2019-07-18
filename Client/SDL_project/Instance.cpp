#include "stdafx.h"
#include "Instance.h"


Instance::Instance()
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
}


Instance::~Instance()
{
}


void Instance::Update()
{
	//I_Physics->Step(1.0f / 100.0f, 6, 2);
}

//void Instance::Render(GL_Renderer& renderer)
//{
//	//for each (auto player in networkPlayers)
//	{
//		//player->Render(renderer);
//	}
//}

void Instance::OnEnter(Player& player)
{
	// Set instance player
	I_Player = player;
	I_Player.InitPhysics(I_Physics.get(), b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
}

void Instance::OnExit(Player& player)
{
	// Return instance player
	//player = *I_Player;
}


