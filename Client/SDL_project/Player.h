#pragma once
#include "Character.h"
#include "LightSource.h"
#include "Timer.h"
#include "CollisionIdentifier.h"

class Player : public Character
{
public:
	Player();
	~Player();
	std::shared_ptr<Player> getSharedPointer();
	Player LoadFromJson(json playerData);
	//! Render the player polymorphed from game object
	void Render(GL_Renderer &renderer);
	
	//! Renders the characters clothes
	void renderCharacterBody(GL_Renderer& renderer, int index, bool flipSprite);
	//! Move the player to the position
	void Move(Player::MovementDirection direction);
	void Move(glm::vec2 direction);

	void AssignSprites(GL_Renderer& renderer, int index, bool flip);
	json getPlayerJson();

	glm::vec2 renderOffset;
	glm::vec2 screenCenter;
	int xOffset, yOffset;

	//! Player clothes
	Clothing PlayerClothes;

	//! @Overloaded
	//Gives an object the player collided with 
	void collidedWith(CollisionIdentifier& objectIdentity);



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

	LightSource playerLight;

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

	//! Player Name
	std::string playerName;
private:
	std::shared_ptr<Player> playerPointer = nullptr;
	float speed = 20.0f;
	float walkSpeed = 20.0f;
	float runSpeed = 40.0f;
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

	//! Default colours
	vec3 hairColour = { 255,255,255 };
	vec3 eyeColour = { 255,255,255 };
	vec3 topColour = { 255,255,255 };
	vec3 bottomColour = { 255,255,255 };

	vec3 bodyColour = { 255,224,189 };
	//! Texture locations
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Characters\\Accessories\\Clothing\\";

	std::string CharacterTextureLocation = "Resources\\Characters\\";
	std::string CharacterEarsTextureLocation = "Resources\\Characters\\Accessories\\Ears\\";
	std::string CharacterEyesTextureLocation = "Resources\\Characters\\Accessories\\Eyes\\";
	std::string CharacterHairTextureLocation = "Resources\\Characters\\Accessories\\Hair\\";

	//! Gender Textures
	//Texture male;
	//Texture female;
	Texture2D nakedBody;
	Texture2D hair;
	Texture2D eyes;
	Texture2D ears;
	Texture2D shadow;
	Texture2D top;
	Texture2D bottom;

	//! Ear Textures
	Texture2D aquaticEar;
	Texture2D catEar1;
	Texture2D catEar2;
	Texture2D elfEar1;
	Texture2D elfEar2;
	Texture2D elfEar3;
	Texture2D elfEar4;
	Texture2D elfEar5;
	Texture2D elfEar6;
	Texture2D human;
	

	Texture2D eye1;
	Texture2D eye2;
	Texture2D eye3;
	Texture2D eye4;
	Texture2D eye5;
	Texture2D eye6;
	Texture2D eye7;
	Texture2D eye8;
	Texture2D eye9;
	Texture2D eye10;
	Texture2D eye11;
	Texture2D eye12;
	Texture2D eye13;

	Texture2D hair1;
	Texture2D hair2;
	Texture2D hair3;
	Texture2D hair4;
	Texture2D hair5;
	Texture2D hair6;
	Texture2D hair7;
	Texture2D hair8;


	//!Shadow
	Texture2D playerShadow;

	//! Texture for the Character
	Texture2D characterIdleTexture;
	Texture2D walkTexture;
	Texture2D sideBlinkTexture;
	Texture2D shortHairTexture;
	Texture2D longHairTexture;
	Texture2D eyesTexture;

	//! Texture for the clothes
	Texture2D femaleTop1;
	Texture2D femaleTop2;
	Texture2D femaleBottom1;
	Texture2D femaleBottom2;

	//! Animations
	Animation walkHorizontalAnimation;
	Animation walkVerticalAnimation;
	Animation legFlipIdleAnimation;

	Animation fishingCast;
	Animation fishingReel;

	//! Idle and blink timers
	Timer idleAnimationTimer;
	Timer blinkSpeed;
	bool blink = false;
	//! How often the player blinks in ms
	float blinkFrequency = 5000.0f;
	//! Length the player has their eyes closed
	float blinkDuration = 100.0f;
};

