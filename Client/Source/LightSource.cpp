#include "stdafx.h"
#include "LightSource.h"


LightSource::LightSource()
{
	//! get a random numer to start with (REDO this)
	this->lightID = SDL_GetTicks() * 1000.0f;
	//this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\streetLight.png");
}

LightSource::LightSource(glm::vec2 position, LightSource::LightType type)
{
	this->position = position;
	this->lightID = (int)SDL_GetTicks() * 100.0f;
	this->lightType = type;
}

std::shared_ptr<LightSource> LightSource::getPointer()
{
	auto light = std::make_shared<LightSource>(*this);
	return light;
}


LightSource::~LightSource()
{
	this->lightType = LightType::noLight;
	this->isOn = false;
	this->size = { 0.0f,0.0f };
	this->position = { 0.0f,0.0f };
	this->lightID = 0;
}

void LightSource::Render(GL_Renderer& renderer)
{
	switch (this->lightType)
	{
	case LightType::campfire:
		if(this->Sprite.Width == 0)
			this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 471);
		
		light.colour = { 1.0f, 1.0f, 1.0f, 2.0f };
		flicker = lightIntensity + ((sin(SDL_GetTicks() / 75.0f) + 1.25) / 80.0) ; // flicker speed, flicker lightness increase, reduce intensity
		light.position = { this->position, lightIntensity + flicker };
		if (isOn) // Remove the lgith if off
			renderer.lights[lightID] = light;
		else
			renderer.lights.erase(lightID);
		break;
		// Lantern
	case LightType::lantern:
		if (this->Sprite.Width == 0)
			this->Sprite = ResourceManager::GetAtlasTexture("roguelike", 1025);
		this->size.y = Sprite.Height;
		this->size.x = Sprite.Width;
		light.colour = { 1.0f, 1.0f, 1.0f, 2.0f };
		light.position = { this->position, lightIntensity };
		if (isOn) // Remove the lgith if off
			renderer.lights[lightID] = light;
		else
			renderer.lights.erase(lightID);
		break;

		// Street light
	case LightType::streetLight:
		if (this->Sprite.Width == 0)
			this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\streetLight.png"), this->NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\streetLight.png");
		this->size.y = Sprite.Height;
		this->size.x = Sprite.Width;
		light.colour = { 1.0f,0.4f,0.0f, 0.3f };

		light.position = { this->position, lightIntensity };
		
		if (isOn) // Remove the light if off
			renderer.lights[lightID] = light;
		else
			renderer.lights.erase(lightID);
		break;

		// PLAYER LGIHT
	case LightType::playerAmbientLight:
		lightIntensity = 0.15f;
		light.colour = { 0.9f, 0.8f, 0.9f , 0.5f };
		light.position = { this->position, lightIntensity };
		
		if (isOn) // Remove the lgith if off
			renderer.lights[lightID] = light;
		else
			renderer.lights.erase(lightID);
		break;

	case LightType::npcAmbientLight:
		lightIntensity = 0.25f;
		light.colour = { 0.9f, 0.8f, 0.9f , 0.5f };
		light.position = { this->position, lightIntensity };

		if (isOn) // Remove the lgith if off
			renderer.lights[lightID] = light;
		else
			renderer.lights.erase(lightID);
		break;

		// FIREFLY
	case LightType::fireflyLight:
		lightIntensity = 0.005f;
		light.colour = { 0.3f, 0.3f, 0.1f , 0.1f };
		light.position = { this->position, lightIntensity };

		if (isOn) // Remove the lgith if off
			renderer.lights[lightID] = light;
		else
			renderer.lights.erase(lightID);
		break;
	}
	

	if(this->Sprite.Width > 0 && this->Sprite.Height > 0)
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, flipSprite);
}