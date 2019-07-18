#include "stdafx.h"
#include "Crop.h"


Crop::Crop()
{
	this->renderLayer = 3;
	growthTimer.start();
}


Crop::~Crop()
{
}

json Crop::getJson()
{
	json j_crop;
	j_crop["Type"] = getName();
	j_crop["growthStage"] = currentGrowthStage;
	j_crop["X"] = getX();
	j_crop["Y"] = getY();
	j_crop["Size"] = getSize().x;
	return j_crop;
}

void Crop::Render(GL_Renderer & renderer)
{
	if (growthTimer.getTicks() > growthIteratorTime && currentGrowthStage < growthAnim.maxFrames - 1)
		growthTimer.restart(), currentGrowthStage++;
	if (this->wobble)
	{// Rotate away from player
		if (renderer.playerPosition.x < this->position.x)
		{
			if (this->rotation < rotationAmount)
				this->rotation += rotationSpeed;
		}
		else if (renderer.playerPosition.x > this->position.x)
		{
			if (this->rotation > -rotationAmount)
				this->rotation -= rotationSpeed;
		}
	}
	else
	{// Rotate back
		if (rotation != 0.0f)
		{
			if (rotation > -0.1f && rotation < 0.1f)
				rotation = 0.0f;

			if (rotation < 0.0f)
				rotation += rotationSpeed;
			else if (rotation > 0.0f)
				rotation -= rotationSpeed;

		}
	}
	if(this->growthAnim.Sprites.size() > 0 && this->growthAnim.SpriteNormals.size() > 0)
		renderer.RenderSpriteLighting(this->growthAnim.Sprites[currentGrowthStage], this->growthAnim.SpriteNormals[currentGrowthStage], this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });
}

////////////////////////////////////////////////////////
// Sunflower
////////////////////////////////////////////////////////
// Constructor
SunflowerCrop::SunflowerCrop()
{
	growthAnim.maxFrames = totalFrames;
	growthIteratorTime = iteratorTime;
	this->setSize(50,100);
	for (int i = 0; i < growthAnim.maxFrames; i++)
	{
		growthAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("sunflower", i));
		growthAnim.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("sunflower", i));
	}

}
// Destructor
SunflowerCrop::~SunflowerCrop()
{
}
// Get pointer
std::shared_ptr<Crop> SunflowerCrop::getSharedPointer()
{
	auto sharedItem = std::make_shared<SunflowerCrop>(*this); // make shared Item
	return sharedItem;
}

////////////////////////////////////////////////////////
// NootRoot
////////////////////////////////////////////////////////
// Constructor
NootRoot::NootRoot()
{
	setSize(50, 50);
	growthAnim.maxFrames = totalFrames;
	for (int i = 0; i < growthAnim.maxFrames; i++)
	{
		growthAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("crops", i));
		growthAnim.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("crops", i));
	}

}
// Destructor
NootRoot::~NootRoot()
{
}
// Get pointer
std::shared_ptr<Crop> NootRoot::getSharedPointer()
{
	auto sharedItem = std::make_shared<NootRoot>(*this); // make shared Item
	return sharedItem;
}


////////////////////////////////////////////////////////
// Wheat
////////////////////////////////////////////////////////
// Constructor
WheatCrop::WheatCrop()
{
	setSize(50, 50);
	growthAnim.maxFrames = totalFrames;
	for (int i = 0; i < growthAnim.maxFrames; i++)
	{
		growthAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("crops", i));
		growthAnim.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("crops", i));
	}


}
// Destructor
WheatCrop::~WheatCrop()
{
}
// Get pointer
std::shared_ptr<Crop> WheatCrop::getSharedPointer()
{
	auto sharedItem = std::make_shared<WheatCrop>(*this); // make shared Item
	return sharedItem;
}

////////////////////////////////////////////////////////
// Pumpkin
////////////////////////////////////////////////////////
// Constructor
PumpkinCrop::PumpkinCrop()
{
	setSize(50, 50);
	growthAnim.maxFrames = totalFrames;
	for (int i = 0; i < growthAnim.maxFrames; i++)
	{
		growthAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("crops", i));
		growthAnim.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("crops", i));
	}
}
// Destructor
PumpkinCrop::~PumpkinCrop()
{
}
// Get pointer
std::shared_ptr<Crop> PumpkinCrop::getSharedPointer()
{
	auto sharedItem = std::make_shared<PumpkinCrop>(*this); // make shared Item
	return sharedItem;
}

////////////////////////////////////////////////////////
// Lavender
////////////////////////////////////////////////////////
// Constructor
LavenderCrop::LavenderCrop()
{
	setSize(50, 100);
	growthAnim.maxFrames = totalFrames;
	for (int i = 0; i < growthAnim.maxFrames; i++)
	{
		//if (rand() % 2 == 1)
		//{
		//	growthAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("lavender", i + 20));
		//	growthAnim.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("lavender", i + 20));
		//}
		growthAnim.Sprites.push_back(ResourceManager::GetAtlasTexture("lavender", i));
		growthAnim.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("lavender_normal", i));
	}
}
// Destructor
LavenderCrop::~LavenderCrop()
{
}
// Get pointer
std::shared_ptr<Crop> LavenderCrop::getSharedPointer()
{
	auto sharedItem = std::make_shared<LavenderCrop>(*this); // make shared Item
	return sharedItem;
}