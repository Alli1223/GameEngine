#pragma once

/// C++ libraries
//http://www.adammil.net/blog/v125_Roguelike_Vision_Algorithms.html
// https://www.redblobgames.com/articles/visibility/


class Light 
{
public:

	//! Constructor
	Light();
	//! Destructor
	~Light();

	enum LightType
	{
		noLight,
		campFire,
		torch,
		streetLight
	} lightType;
	glm::vec3 position;
	glm::vec4 colour;
	glm::vec3 falloff;
private:

};

