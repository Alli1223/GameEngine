#pragma once
#include "GameObject.h"
#include "LightSource.h"
class Animal : public GameObject
{
public:
	Animal();
	~Animal();

	virtual void Render(GL_Renderer& renderer);
	LightSource light;
};

