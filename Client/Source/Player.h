#pragma once
#include "Character.h"



class Player : public Character
{
public:
	Player();
	~Player();

	CollisionIdentifier colisionIdentity;
	std::shared_ptr<Player> getSharedPointer();
	Player LoadFromJson(json playerData);
	//! Render the player polymorphed from game object
	void Render(GL_Renderer &renderer);
	
	//! Renders the characters clothes
	void renderCharacterBody(GL_Renderer& renderer, int index, bool flipSprite);
	//! Move the player to the position
	void Move(Player::MovementDirection direction);
	virtual void Move(glm::vec2 position);


	json getPlayerJson();

	glm::vec2 renderOffset;
	glm::vec2 screenCenter;
	int xOffset, yOffset;

	//! @Overloaded
	//Gives an object the player collided with 
	void collidedWith(CollisionIdentifier& objectIdentity);

	virtual void Update();

	Animation getWalkAnimation() { return walkHorizontalAnimation; }
	// Get and set body colours
	vec3 gethairColour() { return hairColour; }
	vec3 getEyeColour() { return eyeColour; }
	vec3 getJacketColour() { return topColour; }
	vec3 getJeansColour() { return bottomColour; }
	vec3 getBodyColour() { return bodyColour; }
	int setHairColour(int r, int g, int b) { return hairColour.r = r, hairColour.g = g, hairColour.b = b; }
	int setEyeColour(int r, int g, int b) { return eyeColour.r = r, eyeColour.g = g, eyeColour.b = b; }
	int setJacketColour(int r, int g, int b) { return topColour.r = r, topColour.g = g, topColour.b = b; }
	int setJeansColour(int r, int g, int b) { return bottomColour.r = r, bottomColour.g = g, bottomColour.b = b; }
	int setBodyColour(int r, int g, int b) { return bodyColour.r = r, bodyColour.g = g, bodyColour.b = b; }
	vec3 setBodyColour(vec3 colour) { return bodyColour = colour; }
	vec3 setEyeColour(vec3 colour) { return eyeColour = colour; }
	vec3 setHairColour(vec3 colour) { return hairColour = colour; }
	vec3 setTopColour(vec3 colour) { return topColour = colour; }
	vec3 setBottomColour(vec3 colour) { return bottomColour = colour; }

	//! Inventory
	Inventory inventory;



	bool pressingUseKey = false;

	// list of player actions for animations
	enum PlayerActions
	{
		none,
		fishingCasting,
		fishingReeling,
		digging,
		hoeing,
		harvesting,
		sytheing
	} playerAction;

	//! Getters and setters for speed
	float getSpeed() { return speed; }
	float setSpeed(float newSpeed) { return speed = newSpeed; }
	float getRunSpeed() { return runSpeed; }
	float getWalkSpeed() { return walkSpeed; }

	int getRenderLayer() { return renderLayer; }
	int setRenderLayer(int newLayer) { return renderLayer = newLayer; }

	//! Player Name
	std::string playerName;
private:
	std::shared_ptr<Player> playerPointer = nullptr;
	//! Speed is variable
	float speed = 10.0f;
	//! Walk and run speed are constants
	float walkSpeed = 10.0f;
	float runSpeed = 20.0f;
	int renderLayer = 3;
	//! Render the player
	void RenderPlayer(GL_Renderer& renderer, Camera& camera);
	//! Load the needed Resources
	void LoadResources();
	//! Json data to store player stats
	json playerJsondata;
	//! Whether the player is able to move
	bool playerCanMove = true;
	//! Pixel size of the player sprite in the spritesheet
	int pixelSize = 64;



};

