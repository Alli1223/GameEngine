#pragma once
#include "Timer.h"
#include "GameObject.h"
#include "Animation.h"
#include "LightSource.h"
#include "CropSquare.h"
#include "Furniture.h"
class CellAssignment; // Define CellAssignment as forward decoration

struct Vegetation : public GameObject
{
	enum VegeType
	{
		longGrass,
		wheat,
		fern,
		shrub
	}vegeType;
	//! Default constructor
	Vegetation::Vegetation()
	{}
	// Construct with position
	Vegetation::Vegetation(glm::vec2 pos, VegeType type)
	{
		this->renderLayer = 3;
		this->position = pos;
		this->setSize(100, 100);
		animation.maxFrames = 7;
		//for(int i = 0; i < animation.maxFrames; i++)
		//	animation.Sprites.push_back(ResourceManager::GetAtlasTexture("crops", i));
		switch (type)
		{
		case VegeType::longGrass:
			this->Sprite = ResourceManager::GetAtlasTexture("crops", 6);
			this->NormalMap = ResourceManager::GetAtlasTexture("crops", 6);
			break;
		case VegeType::fern:
			this->Sprite = ResourceManager::GetAtlasTexture("flowers", 6);
			this->NormalMap = ResourceManager::GetAtlasTexture("flowers_normal", 6);
			break;
		case VegeType::shrub:
			this->Sprite = ResourceManager::GetAtlasTexture("flowers", 60);
			this->NormalMap = ResourceManager::GetAtlasTexture("flowers_normal", 60);
			break;
		}
		this->vegeType = type;
	}


	std::shared_ptr<Vegetation> getPointer()
	{
		auto sharedItem = std::make_shared<Vegetation>(*this);
		return sharedItem;
	}
	Animation animation;

	void Render(GL_Renderer& renderer)
	{

		if (walkedOver)
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

		renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->colour, { false, false });
		walkedOver = false;
	}
	bool walkedOver = false;
private:
	float rotationSpeed = 0.05f;
	float rotationAmount = 0.3f;
};

class Cell : public GameObject
{
public:

	//! A constructor
	Cell();
	//! An alternate constructor
	/*!
	This constructor requires an X and Y for the Cell
	*/
	Cell(b2World* physicsWorld, int x, int y, int layer, std::string type);
	//! Without specified layer ( defaults to 0)
	Cell(b2World* physicsWorld, int x, int y, std::string type);
	Cell(b2World* physicsWorld, json cellData);

	//! A destructor 
	~Cell();
	void Clear();

	//! Item that is in the cell
	std::shared_ptr<Item> CellItem = nullptr;

	//! Gets the cells data and returns it in json format
	json GetJson();

	//! Assign the cells type
	void AssignType(std::string type, bool Istype);
	void AssignType(int layer, std::string type);
	void AssignType(int layer);
	//! Render the cell
	void Render(GL_Renderer& renderer);


	// Getter functions
	//! Gets the Cell's X value
	int getX() const { return x; }
	//! Gets the Cell's Y value
	int getY() const { return y; }

	// Setter functions
	//! Sets the Cells X value
	int setX(int newX) { return x = newX; }
	//! Sets the Cells Y value
	int setY(int newY) { return y = newY; }
	//! Sets the Cells X and Y values
	int setPos(int newX, int newY) { return x = newX, y = newY; }

	//! Whether the cell is part of a room
	bool isRoom = false;
	//! Whether the cell is walkable
	bool isWalkable = true;

	//! Variables used for terrain
	double terrainElevationValue = 0;
	double climate = 0;

	//! Cell types
	bool isGrass = false;
	bool isLongGrass = false;
	bool isDirt = false;

	bool isTree = false;
	bool isWheat = false;
	bool isCrop = false;

	bool isWater = false;
	bool isFishingBob = false;
	bool isSand = false;
	bool isSnow = false;
	bool isWood = false;
	bool isStone = false;
	bool isRock = false;
	bool isWall = false;

	bool isDisplayCase = false;

	enum GroundType
	{
		empty,
		grass1,
		grass2,
		dirt1,
		dirt2
	}groundType;

	void SetGroundType(Cell::GroundType type ,int layer);


	enum Orientation
	{
		none,
		topLeft,
		topMiddle,
		topRight,
		middleLeft,
		middle,
		middleRight,
		bottomLeft,
		bottomMiddle,
		bottomRight,

		inv_topLeft,
		inv_topRight,
		inv_bottomLeft,
		inv_bottomRight,

		alone
	} orientation;

	void SetOrientation(Cell::Orientation newOrientation) { orientation = newOrientation; }

	Texture2D layerdSprite;
	Texture2D layerdSprite_normal;

	//std::string cellTextures;
	std::map<int, std::string> cellTextureLayer;

	//! Any dense vegetation on the cell
	std::vector<std::shared_ptr<Vegetation>> vegetation;
	
	CropSquare& GetCropSquare();
	std::shared_ptr<CropSquare> cropSquare;
	//! Lights that are placed on the cell
	std::shared_ptr<LightSource> light;

	int getCellSize() { return cellSize; }
	int setCellSize(int newSize) { return cellSize = newSize; }
	//! used to save where the tile is within the chunk
	glm::ivec2 tilePos;

	Animation animation;
private:
	
	//! Used to reference where the tile is in the world
	int x, y;
	int cellSize = 100;
	void Init();

	
};
