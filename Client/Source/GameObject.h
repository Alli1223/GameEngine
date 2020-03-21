#pragma once
#include "Texture2D.h"
#include "GL_Renderer.h"
#include <Box2D/Box2D.h>
#include "CollisionIdentifier.h"
#include "Animation.h"
class GameObject
{
public:
	//! Constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	~GameObject();

	//! Draw sprite
	virtual void Render(GL_Renderer &renderer);

	void RenderAnimation(Animation& anim, std::string atlasName);

	//! Override Get Json Data
	virtual json GetJson();

	//! Getters and setters for positions
	float getX() { return position.x; }
	float getY() { return position.y; }
	
	float setX(float newX) { return position.x = newX; }
	float setY(float newY) { return position.y = newY; }

	float GetDistance(vec2 pointA, vec2 pointB);
	//float lerpDistance(vec2 position);

	//! Set the position of the object
	glm::vec2 setPosition(float newX, float newY) { return { position.x = newX, position.y = newY }; }
	virtual glm::vec2 setPosition(glm::vec2 newPosition) { return position = newPosition; }
	glm::vec2 getPosition();
	//! Getters and setters for velocity
	float getSpeed() { return speed; }
	float setSpeed(float newSpeed) { return speed = newSpeed; }
	glm::vec2 getVelocity() { return velocity; }
	float setVelocity(float x, float y) { return velocity.x = x, velocity.y = y; }
	float setSize(float x, float y) { return size.x = x, size.y = y; }
	glm::vec2 setSize(glm::vec2 newSize) { return size = newSize; }
	glm::vec2 getSize() { return size; }
	glm::vec2 getHalfSize() { return size / 2.0f; }
	float getWidth() { return size.x; }
	float getHeight() { return size.y; }

	//! Set or Get Rotation
	GLfloat getRotation() { return rotation; }
	GLfloat setRotation(GLfloat newRotation) { return rotation = newRotation; }

	// Flip the sprite horizontally or vertiacally
	std::pair<bool, bool> flipSprite;


	//! Rectangular Collision detection
	bool collidesWith(GameObject object);
	virtual void collidedWith(CollisionIdentifier& objectIdentity);
	//! Transparency normalized between 0 and 1
	float transparency = 1.0;

	float xMeters;
	float yMeters;

	//! Render state
	Texture2D Sprite;
	Texture2D NormalMap;

	//! What layer the object gets rendererd
	//* 1: Ground3 is player level *//
	int renderLayer = 0;
	bool RenderAbovePlayer = false;


	b2Body* getBody() { return rigidBody; }
	b2Fixture* getFixture() { return fixture; }
	

	// Physics stuff
	b2Body* rigidBody = nullptr;
	b2Fixture* fixture = nullptr;
	b2ContactListener* contactListener = nullptr;
	b2World* physicsptr = nullptr;

	//! Initilise the object in the physics world
	void InitPhysics(b2World* physicsWorld, b2BodyType type, float density, float friction);
	void InitPhysics(b2World* physicsWorld, CollisionIdentifier& objectIdnetifier, b2BodyType type, float density, float friction);
	bool hasPhysics = false;

	//! Used to decrese the sprites to a MKS factor for the physics simulation
	float physicsScaleDown = 0.001f;
	//! Used to rescale the sprites to pixel size from MKS size
	float physicsScaleUp = 1000.0f;

protected:
	const GLchar* spritePath;
	const GLchar* spritePath_normal;
	
	virtual void InitSprite();
	bool initalised = false;
	//! Values
	float speed = 1.0f;
	glm::vec2 position, size, velocity;
	glm::vec3 colour = { 0,0,0 };
	GLfloat rotation;
};

