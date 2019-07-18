#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Timer.h"
///////////////////////////////////////////////////////////////////////////////////////
// Class: Crop
// used as a polymorphed object to store the diffenret types of crops that inherit this class
// Must have:
// @ std:string cropName;
// @ Animation containing the growth stages
///////////////////////////////////////////////////////////////////////////////////////
class Crop : public GameObject
{
public:
	// Constructor and Destructor
	Crop();
	~Crop();
	//! Get the current stage
	virtual int getCurrentGrowthStage() { return currentGrowthStage; }
	virtual int setCurrentGrowthStage(int newStage) { return currentGrowthStage = newStage; }
	//! Get total stages the plant has
	virtual int getTotalStages() { return totalStages; }
	//! Get the animation
	virtual Animation& getAnimation() { return growthAnim; }
	//! Get the crops name
	virtual std::string getName() { return cropName; }

	json getJson();

	void Render(GL_Renderer& renderer);

protected:
	//! Animation stores the frames of the sprite
	Animation growthAnim;
	Timer growthTimer;

	bool wobble = false;

	// Used for plant wobble
	float rotationSpeed = 0.05f;
	float rotationAmount = 0.3f;

	//! Total stages the plant has
	int totalStages = 3;
	int currentGrowthStage = 0;
	//! Time it takes for plant to grow each stage
	float growthIteratorTime = 10000;
	//! Name
	std::string cropName = "NULL";
};

////////////////////////////////////////////////////////
// Sunflower
////////////////////////////////////////////////////////
struct SunflowerCrop : public Crop
{
	//! Constructor and Destructor
	SunflowerCrop::SunflowerCrop();
	SunflowerCrop::~SunflowerCrop();

	//! Get a shared pointer to this object
	std::shared_ptr<Crop> getSharedPointer();
	//json getCropJson();
	std::string getName() { return cropName; }
	
private:
	int totalStages = 4;
	int totalFrames = 13;
	//! Time it takes for plant to grow each stage
	float iteratorTime = 1000;
	std::string cropName = "Sunflower";
};

////////////////////////////////////////////////////////
// NootRoot
////////////////////////////////////////////////////////

struct NootRoot : public Crop
{
	NootRoot::NootRoot();
	NootRoot::~NootRoot();
	//! Get a shared pointer to this object
	std::shared_ptr<Crop> getSharedPointer();
	//json getCropJson();
	std::string getName() { return cropName; }

private:
	int totalStages = 3;
	int totalFrames;
	std::string cropName = "NootRoot";
};

////////////////////////////////////////////////////////
// Wheat
////////////////////////////////////////////////////////

struct WheatCrop : public Crop
{
	WheatCrop::WheatCrop();
	WheatCrop::~WheatCrop();
	//! Get a shared pointer to this object
	std::shared_ptr<Crop> getSharedPointer();
	//json getCropJson();
	std::string getName() { return cropName; }

private:
	std::string cropName = "Wheat";
	int totalStages = 3;
	int totalFrames = 7;
};

////////////////////////////////////////////////////////
// Pumpkin
////////////////////////////////////////////////////////

struct PumpkinCrop : public Crop
{
	PumpkinCrop::PumpkinCrop();
	PumpkinCrop::~PumpkinCrop();
	//! Get a shared pointer to this object
	std::shared_ptr<Crop> getSharedPointer();
	//json getCropJson();
	std::string getName() { return cropName; }

private:
	std::string cropName = "Pumpkin";
	int totalStages = 3;
	int totalFrames;
};

////////////////////////////////////////////////////////
// Lavender
////////////////////////////////////////////////////////

struct LavenderCrop : public Crop
{
	LavenderCrop::LavenderCrop();
	LavenderCrop::~LavenderCrop();
	//! Get a shared pointer to this object
	std::shared_ptr<Crop> getSharedPointer();
	//json getCropJson();
	std::string getName() { return cropName; }

private:
	std::string cropName = "Lavender";
	int totalStages = 3;
	int totalFrames = 10;
};