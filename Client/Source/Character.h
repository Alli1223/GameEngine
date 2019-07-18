#pragma once
#include "Animation.h"
#include "GameObject.h"
#include "Inventory.h"
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

	//! Character Type
	std::string characterType = "NPC";

	//! Position in the world
	glm::vec2 chunkPos, cellPos;

	//! Move the Charater and check for collisions
	void Move(int newX, int newY);

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
protected:
	std::string CharacterDirectory = "Resources\\Characters\\";
	std::string CharacterClothingDirectory = "Resources\\Characters\\Clothing\\";
	std::string PlayerAccessoriesDirectory = "Resources\\Characters\\Accessories\\";

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

