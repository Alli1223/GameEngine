#include "stdafx.h"
#include "Instance.h"
#include "GameSettings.h"
CollisionListener contact;

Instance::Instance()
{
	b2Vec2 gravity(0.0f, 0.0f);
	I_Physics = std::make_unique<b2World>(gravity);
	I_Physics->SetContactListener(&contact);
}


Instance::~Instance()
{
}




void Instance::onEnter(Player& player)
{
	if(GameSettings::currentInstance != nullptr)
		GameSettings::currentInstance->onExit(player);
	GameSettings::currentInstance = this;
	//player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	I_player = player;
	I_player.InitPhysics(I_Physics.get(), player.colisionIdentity, b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	InstanceSetup(I_player);
}

void Instance::InstanceSetup(Player& player)
{
}

void Instance::onExit(Player& player)
{
}



void Instance::Render(GL_Renderer& renderer)
{
	//player.Render(renderer);
}

void Instance::Update()
{
	// Get refresh rate
	I_Physics->Step(1.0f / 100.0f, 6, 2);
}
