#include "stdafx.h"
#include "Cell.h"
#include "CellAssignment.h"

Cell::Cell()
{
	//ResourceManager::LoadAtlas("roguelike", "Resources\\Sprites\\SpriteSheets\\roguelikeSheet_transparent.png", 56, 16);
	//this->Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\wood_Diffuse.png");
	//this->NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\wood_Normal2.png");
}

// Create with a position
Cell::Cell(b2World* physicsWorld, int x, int y, int layer, std::string type)
{
	setX(x);
	setY(y);
	setSize(cellSize, cellSize);
	setPosition(x * cellSize, y * cellSize);
	cellTextureLayer[layer] = type;
	AssignType(layer, type);
	physicsptr = physicsWorld;

}
// Create with a position
Cell::Cell(b2World* physicsWorld, int x, int y, std::string type)
{
	setX(x);
	setY(y);
	setSize(cellSize, cellSize);
	setPosition(x * cellSize, y * cellSize);
	cellTextureLayer[0] = type;
	AssignType(0, type);
	physicsptr = physicsWorld;
}


void Cell::AssignType(std::string type, bool isType)
{
	cellTextureLayer[0] = type;
	CellAssignment::AssignCell(*this, type, 0);
	if (!isWalkable)
		InitPhysics(physicsptr, b2BodyType::b2_staticBody, 0.0f, 0.0f);
}
void Cell::AssignType(int layer, std::string type)
{
	CellAssignment::AssignCell(*this, type, layer);

	//if (!isWalkable)
	//	InitPhysics(physicsptr, b2BodyType::b2_staticBody, 0.0f, 0.0f);
}

void Cell::Clear()
{
	Cell newCleanCell;
	newCleanCell.setPosition(this->getPosition());
	newCleanCell.setX(this->getX());
	newCleanCell.setY(this->getY());
	newCleanCell.setSize(this->getSize());
	*this = newCleanCell;
}

void Cell::Init()
{
	//AssignType(cellType, true);
	initalised = true;
}

CropSquare& Cell::GetCropSquare()
{
	//Create crop tile if it doesnt exist
	if (cropSquare == nullptr)
	{
		CropSquare newCropSquare(this->getPosition(), cellSize);
		this->cropSquare = std::make_shared<CropSquare>(newCropSquare);
		return *this->cropSquare;
	}
	else
		return *this->cropSquare;
}

void Cell::Render(GL_Renderer& renderer)
{
	if (!hasPhysics && !isWalkable && physicsptr != nullptr)
		InitPhysics(physicsptr, b2BodyType::b2_staticBody, 10.0f, 1.0f);
	if (hasPhysics && getBody() != nullptr)
		this->setPosition(getBody()->GetPosition().x *  physicsScaleUp, getBody()->GetPosition().y  * physicsScaleUp);// Set sprite position from scaled down plysics
	
	if (CellItem != nullptr)
		CellItem->Render(renderer);
	
	if (isWater)
	{
		animation.OnAnimate();
		if (animation.getCurrentFrame() < animation.Sprites.size())
		{
			this->Sprite = animation.Sprites[animation.getCurrentFrame()];
			this->NormalMap = animation.SpriteNormals[animation.getCurrentFrame()];
			this->layerdSprite = animation.Sprites[animation.getCurrentFrame()];
			this->layerdSprite_normal = animation.SpriteNormals[animation.getCurrentFrame()];
		}
	}
	
	// Render sprite
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });
	// If the cell has a layerd sprite
	if (layerdSprite.Width > 0 || layerdSprite.Height > 0)
		renderer.RenderSpriteLighting(this->layerdSprite, this->layerdSprite_normal, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });

	if (vegetation.size() > 0)
	{
		for (int i = 0; i < vegetation.size(); i++)
			vegetation[i]->Render(renderer);
	}
	if (this->light != nullptr)
	{
		this->light->Render(renderer);
	}
	if (this->cropSquare != nullptr)
	{
		this->cropSquare->Render(renderer);
	}
}

// Create with json data
Cell::Cell(b2World* physicsWorld, json cellData)
{
	int x = cellData.at("X").get<int>();
	int y = cellData.at("Y").get<int>();
	int tileX = cellData.at("TileX").get<int>();
	int tileY = cellData.at("TileY").get<int>();
	int width = cellData.at("Width").get<int>();
	int height = cellData.at("Height").get<int>();
	setSize(width, height);
	setPos(x, y);
	setPosition(x * cellSize, y * cellSize);
	tilePos = { tileX, tileY };
	json textures = cellData.at("Layers");

	for (auto& texture : textures)
	{
		int layer = texture.at("Layer");
		std::string j_sprite = texture.at("Sprite");
		this->cellTextureLayer[layer] = j_sprite;
		AssignType(layer, j_sprite);
	}

	json j_vegetation = cellData.at("Vegetation");
	for (auto& item : j_vegetation)
	{
		
		int x = item.at("X").get<float>();
		int y = item.at("Y").get<float>();
		int type = item.at("Type").get<int>();
		Vegetation newVege({ x,y }, Vegetation::VegeType(type));
		int width = item.at("W").get<int>();
		int height = item.at("H").get<int>();
		
		int layer = item.at("Layer").get<int>();
		newVege.setPosition(x, y);
		newVege.setSize(width, height);
		newVege.renderLayer = layer;
		newVege.vegeType = Vegetation::VegeType(type);
		vegetation.push_back(newVege.getPointer());
	}
	if (cellData.count("CropSquare") > 0)
	{
		json crops = cellData.at("CropSquare");

		CropSquare newCropSquare(crops);
		this->cropSquare = std::make_shared<CropSquare>(newCropSquare);
	}

	if (cellData.count("Item") > 0)
	{
		json itemData = cellData.at("Item");
		Item item2(itemData);
		std::shared_ptr<Item> item = item2.ConstructFromJson(itemData);
		this->CellItem = item;
	}

	//cellType = cellData.at("Type").get<std::string>();
}

Cell::~Cell(){
}

// Get the cell data from 
json Cell::GetJson()
{	
	json cellData;
	cellData["X"] = x;
	cellData["Y"] = y;
	cellData["TileX"] = tilePos.x;
	cellData["TileY"] = tilePos.y;
	cellData["Width"] = getSize().x;
	cellData["Height"] = getSize().y;

	json textures;
	for (auto& texture : cellTextureLayer)
	{
		json jsonTex;
		jsonTex["Layer"] = texture.first;
		jsonTex["Sprite"] = texture.second;
		textures.push_back(jsonTex);
	}
	// Vegetaion
	json jsonVegetation;
	for (auto& vegetat : vegetation)
	{
		json jsonVege;
		jsonVege["X"] = vegetat->getPosition().x;
		jsonVege["Y"] = vegetat->getPosition().y;
		jsonVege["W"] = (int)vegetat->getSize().x;
		jsonVege["H"] = (int)vegetat->getSize().y;
		jsonVege["Layer"] = vegetat->renderLayer;
		jsonVege["Type"] = vegetat->vegeType;
		jsonVegetation.push_back(jsonVege);
	}
	cellData["Vegetation"] = jsonVegetation;

	// Crops
	
	if (cropSquare != nullptr)
	{
		json j_cropSquare;
		j_cropSquare["X"] = cropSquare->getX();
		j_cropSquare["Y"] = cropSquare->getY();
		json j_crops;
		for (auto& crop : cropSquare->cropTiles)
		{
			if(crop != nullptr)
				j_crops.push_back(crop->getJson());
		}
		j_cropSquare["CropTiles"] = j_crops;
		cellData["CropSquare"] = j_cropSquare;
	}
	

	cellData["Layers"] = textures;

	if(isDirt)
		cellData["Dirt"] = isDirt;
	if(isGrass)
		cellData["Grass"] = isGrass;
	if (isWater)
		cellData["Water"] = isWater;
	if (isSand)
		cellData["Sand"] = isSand;
	if(isWood)
		cellData["Wood"] = isWood;
	if(isStone)
		cellData["Stone"] = isStone;
	if (isRock)
		cellData["Rock"] = isRock;
	if (isTree)
		cellData["Tree"] = isTree;
	if(isWheat)
		cellData["Wheat"] = isWheat;

	if (CellItem != nullptr)
		cellData["Item"] = CellItem->GetJson();
	
	return cellData;
}

