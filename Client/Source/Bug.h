#pragma once
#include "Animal.h"
#include "Icon.h"
class Bug : public Animal
{
public:
	Bug();
	~Bug();

	virtual void Render(GL_Renderer& renderer);

	Icon icon;


};

struct Firefly : public Bug
{
public:
	Firefly::Firefly()
	{
		light.lightType = LightSource::LightType::fireflyLight;
		this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 666);
		this->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 666);
		this->icon.Background = ResourceManager::GetAtlasTexture("roguelike", 333);

		this->renderLayer = 3;
		this->setSize(10, 10);
	}
	Firefly::~Firefly()
	{
		light.isOn = false;
		light.~LightSource();
		this->position = { 0.0f, 0.0f };
		this->size = { 0.0f,0.0f };
	}

	void Render(GL_Renderer& renderer)
	{
		//this->InitPhysics(renderer.p_World.get(), b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
		
		vec2 ran = { (float)(sin(rand() % 300) + cos(SDL_GetTicks() / 500.0f)) , (float)(sin(rand() % 300)) + cos(SDL_GetTicks() / 500.0f) };
		ran /= 10000.0f;
		this->getBody()->ApplyForceToCenter(b2Vec2(ran.x, ran.y), true);
		this->setPosition({ this->getBody()->GetPosition().x * physicsScaleUp,this->getBody()->GetPosition().y * physicsScaleUp });
		//this->setPosition(this->getPosition() + ran);
		light.setPosition(this->getPosition());
		light.Render(renderer);
	}
	//! Get a shared pointer to this object
	std::shared_ptr<Bug> getSharedPointer()
	{
		auto sharedItem = std::make_shared<Firefly>(*this); // make shared Item
		return sharedItem;
	}
private:
};