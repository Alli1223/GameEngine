#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Timer.h"
#include "CropTile.h"

//////////////////////////////////////////////////////////////////////
// Class: Crops
// Description:
// holds four cells with a tilled soil sprite and a crop object
// Orients the tilled soil
class CropSquare : public GameObject
{
public:
	CropSquare::CropSquare(glm::vec2 pos, int cellSize);
	// Create from json file
	CropSquare::CropSquare(json data);
	~CropSquare();
	std::vector<std::shared_ptr<CropTile>> cropTiles;

	void OrientCell();
	//! position of where the cursor is on the cell to get which corner of the cell to place
	void HoeGround(glm::vec2 pos);
	std::shared_ptr<CropTile>& GetCropTile(glm::vec2 pos);
	
	void Render(GL_Renderer& renderer);
	
	std::shared_ptr<CropSquare> getPointer()
	{
		auto sharedItem = std::make_shared<CropSquare>(*this);
		return sharedItem;
	}
	bool wobble = false;
	

	//! Growth animation
	Animation animation;

private:

	void CreateCropTile(int vectorPos, glm::vec2 position);
	float rotationSpeed = 0.05f;
	float rotationAmount = 0.3f;

	int currentGrowthStage = 0;
	Timer growthTimer;
	float growthIteratorTime = 10000;

	int cropTileSize = 50;
};

