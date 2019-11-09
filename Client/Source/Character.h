#pragma once
#include "Animation.h"
#include "GameObject.h"
#include "Inventory.h"
#include "LightSource.h"
#include "Timer.h"
#include "CollisionIdentifier.h"
#include "Projectile.h"
#include "SpeechBubble.h"
class Character : public GameObject
{
public:
	Character();
	~Character();	
	//! Gets and the agents health
	float getHealth() { return health; }
	int getTargetRotation() { return targetRotation; }
	//! Sets the characters cellX value
	int setCellX(int newCellX) { return cellX = newCellX; }
	//! Sets the characters cellY value
	int setCellY(int newCellY) { return cellY = newCellY; }
	//! Sets the characters health
	float setHealth(float newHealth) { return health = newHealth; }
	//! Sets rotations
	int setRotation(int newRotation) { return rotation = newRotation; }
	int setTargetRotation(int newTarget) { return targetRotation = newTarget; }
	int setRotationSpeed(int newSpeed) { return rotationSpeed = newSpeed; }
	//! Player movement boolean
	bool setPlayerMoving(bool yayornay) { return isMoving = yayornay; }
	bool isPlayerMoving() { return isMoving; }

	void RotateCharacter(GL_Renderer& renderer);


	//! Renders the characters clothes
	void RenderCharacterBody(GL_Renderer& renderer, int index, bool flipSprite);
	void AssignSprites(GL_Renderer& renderer, int index, bool flip);
	//! Character Type
	std::string characterType = "NPC";

	//! Position in the world
	glm::vec2 chunkPos, cellPos;

	//! Move the Charater and check for collisions
	void Move(int newX, int newY);

	//! Text for the character
	SpeechBubble speechBubble;

	enum MovementDirection
	{
		none,
		left,
		right,
		up,
		down,
		left_up,
		left_down,
		right_up,
		right_down
	} direction;

	bool isInBuilding = false;

	LightSource playerLight;

	//! Enum for chacter customisation
	typedef struct
	{
		enum HeadWear
		{
			noHeadWear,
			hat1,
			ha2
		}hat;

		enum BodyWear
		{
			noTop,
			femaleTop1,
			femaleTop2,
			maleTop1,
			maleTop2

		}body;

		enum LegWear
		{
			noBottoms,
			femaleBottom1,
			femaleBottom2,
			maleBottom1,
			maleBottom2

		}leg;

	} Clothing;

	typedef struct
	{
		enum Gender
		{
			male,
			female
		} gender;

		enum EarType
		{
			aquatic,
			cat1,
			cat2,
			elf1,
			elf2,
			elf3,
			elf4,
			elf5,
			elf6,
			human
		} earType;

		enum EyeType
		{
			eye1,
			eye2,
			eye3,
			eye4,
			eye5,
			eye6,
			eye7,
			eye8,
			eye9,
			eye10,
			eye11,
			eye12,
			eye13
		} eyeType;

		enum HairType
		{
			hair1,
			hair2,
			hair3,
			hair4,
			hair5,
			hair6,
			hair7,
			hair8
		} hairType;

	} Body;
	//! Characters body options
	Body body;

	//! Character clothes
	Clothing PlayerClothes;

	//! Default colours
	vec3 hairColour = { 255,255,255 };
	vec3 eyeColour = { 255,255,255 };
	vec3 topColour = { 255,255,255 };
	vec3 bottomColour = { 255,255,255 };

	vec3 bodyColour = { 255,224,189 };

protected:
	std::string CharacterDirectory = "Resources\\Characters\\";
	std::string CharacterClothingDirectory = "Resources\\Characters\\Clothing\\";
	std::string PlayerAccessoriesDirectory = "Resources\\Characters\\Accessories\\";

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
private:
	//! Rotation values
	int targetRotation = 0, rotationSpeed = 5;

	//! Integers for the agent's cellX and cellY positions below agent
	int cellX = 0; int cellY = 0;
	//! Point for where the agent is located
	//Point pointLocation;
	//! A double for the agents's health
	float health = 100.0;
	//! If the Character can rotate
	bool incrementalRotating = false;
	//! if the Character is moving
	bool isMoving = false;
};

