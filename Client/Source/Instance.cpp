#include "stdafx.h"
#include "Instance.h"
CollisionListener contact;

Instance::Instance()
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
	I_Physics->SetContactListener(&contact);
	//I_player->setSize(100, 100);
	//I_player->setPosition(100, 100);
}


Instance::~Instance()
{
}

void Instance::onEnter(Player& player)
{
	player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	//I_player = &player;
}

void Instance::onExit(Player& player)
{
}



void Instance::Render(GL_Renderer& Renderer)
{
	//I_player->Render(Renderer);
	
	//level.map->Render(Renderer);
}

void Instance::Update()
{
	// Get refresh rate
	I_Physics->Step(1.0f / 100.0f, 6, 2);
}
