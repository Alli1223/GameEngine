#include "stdafx.h"
#include "CropSquare.h"
// Tile vector positions
////////////////////////////////////
// |0,1|
// |2,3|
////////////////////////////////////
CropSquare::CropSquare(glm::vec2 pos, int cellSize)
{
	this->renderLayer = 3;
	this->position = pos;
	this->setSize(100, 100);
	cropTileSize = cellSize / 2;
	// Create empty tiles
	for (int i = 0; i < 4; i++)
		cropTiles.push_back(nullptr);
	
}

CropSquare::CropSquare(json data)
{
	int thisX = data.at("X");
	int thisY = data.at("Y");
	
	this->setSize(100, 100);
	this->setPosition(thisX, thisY);
	for (int i = 0; i < 4; i++)
		cropTiles.push_back(nullptr);
	json tileData = data.at("CropTiles");
	for (auto& cropTile : tileData)
	{
		CropTile newTile;
		int x = cropTile.at("X");
		int y = cropTile.at("Y");
		int orientation = cropTile.at("orientation");
		int id = cropTile.at("ID");
		bool isTilled = cropTile.at("Tilled");

		if (cropTile.count("Crop") > 0)
		{
			Crop newCrop;
			json crop = cropTile.at("Crop");
			int x = crop.at("X");
			int y = crop.at("Y");
			std::string type = crop.at("Type");
			// TODO: find a way not to this
			if (type == "Wheat")
			{
				WheatCrop wheat;
				int cropGrowStage = crop.at("growthStage");
				wheat.setCurrentGrowthStage(cropGrowStage);
				newTile.crop = std::make_shared<WheatCrop>(wheat);
			}
			if (type == "Sunflower")
			{
				SunflowerCrop sunflower;
				int cropGrowStage = crop.at("growthStage");
				sunflower.setCurrentGrowthStage(cropGrowStage);
				newTile.crop = std::make_shared<SunflowerCrop>(sunflower);
			}
			if (type == "Lavender")
			{
				LavenderCrop newCrop;
				int cropGrowStage = crop.at("growthStage");
				newCrop.setCurrentGrowthStage(cropGrowStage);
				newTile.crop = std::make_shared<LavenderCrop>(newCrop);
			}
			
			//newTile.crop = std::make_shared<Crop>(newCrop);
		}
		newTile.isTilled = isTilled;
		newTile.setPosition(x, y);
		newTile.setSize(cropTileSize, cropTileSize);
		newTile.ID = id;
		newTile.SetOrientation(CropTile::Orientation(orientation));
		cropTiles[id] = std::make_shared<CropTile>(newTile);
	}
}

void CropSquare::CreateCropTile(int vectorPos, glm::vec2 position)
{
	CropTile newCropTile(position, cropTileSize);
	newCropTile.SetOrientation(CropTile::middle);
	newCropTile.ID = vectorPos;
	cropTiles[vectorPos] = std::make_shared<CropTile>(newCropTile);
}

// finds out which tile within the cell has been selected
void CropSquare::HoeGround(glm::vec2 pos)
{
	int halfCropSize = cropTileSize / 2;
	vec2 usePos = pos;
	vec2 thisPos = this->getPosition();
	if(pos.x > getX() - cropTileSize && pos.x < getX() + cropTileSize)
		if (pos.y > getY() - cropTileSize && pos.y < getY() + cropTileSize)
		{
			// Top Left
			if (pos.x < getPosition().x && pos.y < getPosition().y)
			{
				if (cropTiles[0] == nullptr)
					CreateCropTile(0, { getPosition().x - halfCropSize, getPosition().y - halfCropSize });
				cropTiles[0]->isTilled = true;
			}
			// Top Right
			else if (pos.x > getPosition().x && pos.y < getPosition().y)
			{
				if (cropTiles[1] == nullptr)
					CreateCropTile(1, { getPosition().x + halfCropSize, getPosition().y - halfCropSize });
				cropTiles[1]->isTilled = true;
			}
			// Bottom left
			else if (pos.x < getPosition().x && pos.y > getPosition().y)
			{
				if (cropTiles[2] == nullptr)
					CreateCropTile(2, { getPosition().x - halfCropSize, getPosition().y + halfCropSize });
				cropTiles[2]->isTilled = true;
			}
			// Bottom Right
			else if (pos.x > getPosition().x && pos.y > getPosition().y)
			{
				if (cropTiles[3] == nullptr)
					CreateCropTile(3, { getPosition().x + halfCropSize, getPosition().y + halfCropSize });
				cropTiles[3]->isTilled = true;
			}
		}
}

std::shared_ptr<CropTile>& CropSquare::GetCropTile(glm::vec2 pos)
{
	int halfCropSize = cropTileSize / 2;
	// Top Left
	if (pos.x < getPosition().x && pos.y < getPosition().y)
	{
		if (cropTiles[0] != nullptr)
			return cropTiles[0];
		else
			return cropTiles[0];
	}
	// Top Right
	else if (pos.x > getPosition().x && pos.y < getPosition().y)
	{
		if (cropTiles[1] != nullptr)
			return cropTiles[1];
		else
			return cropTiles[1];
	}
	// Bottom left
	else if (pos.x < getPosition().x && pos.y > getPosition().y)
	{
		if (cropTiles[2] != nullptr)
			return cropTiles[2];
		else
			return cropTiles[2];
	}
	// Bottom Right
	else if (pos.x > getPosition().x && pos.y > getPosition().y)
	{
		if (cropTiles[3] != nullptr)
			return cropTiles[3];
		else
			return cropTiles[3];
	}
	else
		return cropTiles[0];// shouldnt do this (find way to return null)
}

void CropSquare::Render(GL_Renderer& renderer)
{
	for each (auto& tile in cropTiles)
	{
		if (tile != nullptr)
			tile->Render(renderer);
	}
}

CropSquare::~CropSquare()
{
}
