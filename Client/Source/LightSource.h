#pragma once
#include "GameObject.h"
#include "Light.h"
class LightSource : public GameObject
{
public:
	//! Constuct without type
	LightSource();
	//! Desconstructor
	~LightSource();

	//! Render polymorphism
	void Render(GL_Renderer& renderer);

	std::shared_ptr<LightSource> getPointer();
	//! Light type
	enum LightType
	{
		noLight,
		campfire,
		streetLight,
		lantern,
		playerAmbientLight,
		npcAmbientLight,
		fireflyLight
	} lightType;

	//! Construct with type
	LightSource(glm::vec2 position, LightSource::LightType type);

	bool isOn = true;

	int getLightID() { return lightID; }

	//! How close the light is to the ground (lower is closer)
	float lightIntensity = 0.075f;

private:
	int lightID;
	Light light;
	Texture2D texture;
	float flicker;
};

