#pragma once
#include "GL_Renderer.h"

class GUI 
{
public:
	GUI();
	GUI(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
	~GUI();

	//! Getters and setters for positions
	float getX() { return position.x; }
	float getY() { return position.y; }

	float setX(float newX) { return position.x = newX; }
	float setY(float newY) { return position.y = newY; }

	//! Set the position of the object
	glm::vec2 setPosition(float newX, float newY) { return { position.x = newX, position.y = newY }; }
	glm::vec2 setPosition(glm::vec2 newPosition) { return position = newPosition; }
	glm::vec2 getPosition() { return position; }
	//! Getters and setters for speed
	float setSize(float x, float y) { return size.x = x, size.y = y; }
	glm::vec2 setSize(glm::vec2 newSize) { return size = newSize; }
	glm::vec2 getSize() { return size; }

	float setWidth(float width) { return size.x = width; }
	float setHeight(float height) { return size.y = height; }
	float getWidth() { return size.x; }
	float getHeight() { return size.y; }
	//! Set or Get Rotation
	GLfloat getRotation() { return rotation; }
	GLfloat setRotation(GLfloat newRotation) { return rotation = newRotation; }

	Texture2D Background;
	float transparency = 1.0;

	//! Render this GUI object
	void Render(GL_Renderer& renderer);

	// Flip the sprite horizontally or vertiacally
	std::pair<bool, bool> flipSprite;
protected:
	virtual void Initalise();
	bool isInitalised = false;
	const GLchar* imageLocation;
	glm::vec2 position, size;
	glm::vec3 colour = { 0,0,0 };
	GLfloat rotation;
};

