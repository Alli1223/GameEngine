#include "stdafx.h"
#include "CropTile.h"

CropTile::CropTile()
{
}
CropTile::CropTile(glm::ivec2 pos, int size)
{
	this->setPosition(pos);
	this->setSize(size, size);
	this->renderLayer = 2;
}
CropTile::~CropTile()
{
}

json CropTile::getJson()
{
	json cropTile;
	cropTile["X"] = getX();
	cropTile["Y"] = getY();
	cropTile["ID"] = ID;
	cropTile["orientation"] = orientation;
	cropTile["Tilled"] = isTilled;

	if(crop != nullptr)
		cropTile["Crop"] = crop->getJson();
	return cropTile;
}

void CropTile::SetOrientation(Orientation orient)
{
	this->orientation = orient;
	switch (orientation)
	{
	case Orientation::topLeft:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 0);
			break;
	case Orientation::topMiddle:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 1);
		break;
	case Orientation::topRight:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 2);
		break;
	case Orientation::middleLeft:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 6);
		break;
	case Orientation::middle:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 7);
		break;
	case Orientation::middleRight:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 8);
		break;
	case Orientation::bottomLeft:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 12);
		break;
	case Orientation::bottomMiddle:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 13);
		break;
	case Orientation::bottomRight:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 14);
		break;

	case Orientation::alone:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 15);
		break;

	case Orientation::horizontalMiddle:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 3);
		break;
	case Orientation::horizontalEndLeft:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 4);
		break;
	case Orientation::horizontalEndRight:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 5);
		break;

	case Orientation::verticalMiddle:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 9);
		break;
	case Orientation::verticalEndTop:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 10);
		break;
	case Orientation::verticalEndBottom:
		this->Sprite = ResourceManager::GetAtlasTexture("tillage", 11);
		break;
	}
}

void CropTile::Render(GL_Renderer& renderer)
{
	if(isTilled)
		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });
	if (crop != nullptr)
	{
		crop->setPosition(this->getPosition());
		crop->Render(renderer);
	}
}
