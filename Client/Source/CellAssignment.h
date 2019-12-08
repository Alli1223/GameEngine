#pragma once
class Cell; // Define Cell as forward decoration

class CellAssignment
{
public:
	
	static void AssignCell(Cell& cell, std::string& type, int layer);
	static void AssignCellFromType(Cell& cell, int layer);
	CellAssignment();
	~CellAssignment();
	static const float ground_layer;
	static const float surface_layer;
	static const float Above_Player;
private:
	


	//static void AssignType(Cell& cell, std::string& type);
};

//! Set  float consts
const float CellAssignment::ground_layer = 0;
const float CellAssignment::surface_layer = 1;
const float CellAssignment::Above_Player = 3;

CellAssignment::CellAssignment()
{

}


CellAssignment::~CellAssignment()
{
}

int getNumber(std::string type)
{
	int number = 0;
	int numberPos = type.find_last_of("_");	// Get the traling digits

	std::string numberString = type.substr(numberPos + 1); // Create a string containing the number
	number = std::atoi(numberString.c_str()); // convert string to int
	return number;
}

void CellAssignment::AssignCell(Cell& cell, std::string& type, int layer)
{
	// Load spring grass texture
	cell.cellTextureLayer[layer] = type;
	cell.isWater = false;
	cell.isGrass = false;
	if (type.compare(0, 12, "Weather_Grass") == 0)
	{

	}

	if (type.compare(0, 12, "Spring_Grass_light") == 0)
	{
		int i = getNumber(type);

		if (type == "Spring_Grass_Light_" + std::to_string(i))
		{
			cell.isGrass = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("spring_grass_light", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("spring_grass_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("spring_grass_light", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("spring_grass_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}

	// Ground sprite sheets
	if (type.compare(0, 14, "Autumn_Ground_") == 0)
	{
		int i = getNumber(type);

		if (type == "Autumn_Ground_" + std::to_string(i))
		{
			cell.isGrass = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("autumn_ground", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("autumn_ground_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("autumn_ground", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("autumn_ground_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}
	if (type.compare(0, 14, "Summer_Ground_") == 0)
	{
		int i = getNumber(type);

		if (type == "Summer_Ground_" + std::to_string(i))
		{
			cell.isGrass = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("summer_ground", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("summer_ground_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("summer_ground", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("summer_ground_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}
	if (type.compare(0, 14, "Winter_Ground_") == 0)
	{
		int i = getNumber(type);

		if (type == "Winter_Ground_" + std::to_string(i))
		{
			cell.isGrass = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("winter_ground", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("winter_ground_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("winter_ground", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("winter_ground_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}
	if (type.compare(0, 14, "Spring_Ground_") == 0)
	{
		int i = getNumber(type);

		if (type == "Spring_Ground_" + std::to_string(i))
		{
			cell.isGrass = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("spring_ground", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("spring_ground_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("spring_ground", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("spring_ground_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}


	if (type.compare(0, 12, "Spring_Dirt") == 0)
	{
		int i = getNumber(type);

		if (type == "Spring_Dirt_" + std::to_string(i))
		{
			cell.isGrass = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("spring_dirt_1", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("spring_dirt_1_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("spring_dirt_1", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("spring_dirt_1_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}

	// Load rock textures
	if (type.compare(0, 4, "Rock") == 0)
	{
		int i = getNumber(type);

		if (type == "Rock_" + std::to_string(i))
		{
			cell.isRock = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("rocks", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("rocks_normal", i);
				cell.renderLayer = 2;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("rocks", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("rocks_normal", i);
				cell.renderLayer = 3;
			}
		}
	}
	// Load flower textures
	if (type.compare(0, 7, "Flowers") == 0)
	{
		int i = getNumber(type);

		if (type == "Flowers_" + std::to_string(i))
		{
			cell.isRock = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("flowers", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("flowers_normal", i);
				cell.renderLayer = 2;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("flowers", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("flowers_normal", i);
				cell.renderLayer = 2;
			}
		}
	}
	// Load roguelike textures
	if (type.compare(0, 9, "Roguelike") == 0)
	{
		int i = getNumber(type);

		if (type == "Roguelike_" + std::to_string(i))
		{
			cell.isRock = true;
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("roguelike", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("roguelike", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("roguelike_normal", i);
				cell.renderLayer = surface_layer;
			}
		}
	}
	// Load general rpg textures
	if (type.compare(0, 10, "RpgSprites") == 0)
	{
		int i = getNumber(type);

		if (type == "RpgSprites_" + std::to_string(i))
		{
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("rpgSprites", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("rpgSprites", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("rpgSprites", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("rpgSprites", i);
				cell.renderLayer = surface_layer;
			}
		}
	}

	// Load water textures
	if (type.compare(0, 17, "water_spriteSheet") == 0)
	{
		int i = getNumber(type);

		if (type == "water_spriteSheet_" + std::to_string(i))
		{
			//WaterCell wcell;
			//cell = wcell;
			cell.isWater = true;
			cell.isWalkable = false;
			cell.animation.maxFrames = 6;
			cell.animation.oscillate = true;
			cell.animation.setFrameRate(750 + rand() % 5000);
			if (layer == 0) // Set the ground sprite
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("water_spriteSheet", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("water_spriteSheet_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("water_spriteSheet", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("water_spriteSheet_normal", i);
				cell.renderLayer = surface_layer;
			}

			cell.animation.Sprites.clear();
			for (int j = 0; j < cell.animation.maxFrames; j++)
			{
				
				cell.animation.Sprites.push_back(ResourceManager::GetAtlasTexture("water_spriteSheet", i + j * 3));
				cell.animation.SpriteNormals.push_back(ResourceManager::GetAtlasTexture("water_spriteSheet_normal", i + j * 3));
			}
		}
	}

	// Load path textures
	if (type.compare(0, 4, "Path") == 0)
	{
		int i = getNumber(type);

		if (type == "Path_" + std::to_string(i))
		{
			if (layer == 0)
			{
				cell.Sprite = ResourceManager::GetAtlasTexture("paths", i);
				cell.NormalMap = ResourceManager::GetAtlasTexture("paths_normal", i);
				cell.renderLayer = ground_layer;
			}
			else
			{
				cell.layerdSprite = ResourceManager::GetAtlasTexture("paths", i);
				cell.layerdSprite_normal = ResourceManager::GetAtlasTexture("paths_normal", i);
				cell.renderLayer = surface_layer;
			}
			
		}
	}



	if (type == "Grass")
	{
		cell.isGrass = true;
		cell.Sprite = ResourceManager::GetAtlasTexture("autumn_ground", 29);
		cell.NormalMap = ResourceManager::GetAtlasTexture("autumn_ground_normal", 29);
		cell.renderLayer = layer;

	}
	if (type == "Sand")
	{
		cell.isSand = true;
		cell.Sprite = ResourceManager::GetAtlasTexture("roguelike", 8);
		cell.NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 8);
		cell.renderLayer = layer;

	}
	if (type == "LongGrass")
	{
		cell.isGrass = true;
		cell.isLongGrass = true;
		float test = sin((float)(rand() % 100)) * 25.0f;
		Vegetation veg({ cell.getPosition().x + test, cell.getPosition().y + test }, Vegetation::VegeType::longGrass);
		cell.vegetation.push_back(veg.getPointer());

	}
	if (type == "Fern")
	{
		cell.isGrass = true;
		cell.isLongGrass = true;

		float test = sin((float)(rand() % 100)) * 25.0f;
		Vegetation veg({ cell.getPosition().x + test, cell.getPosition().y + test }, Vegetation::VegeType::fern);
		cell.vegetation.push_back(veg.getPointer());

	}

	if (type == "Wheat")
	{
		cell.isCrop = true;
		
		WheatCrop wheat;
		//Crops wheat({ cell.getPosition().x, cell.getPosition().y }, Crops::CropType::wheat);
		//cell.crop = wheat.getPointer();

	}


	if (type == "Dirt")
	{
		cell.isDirt = true;
		cell.Sprite = ResourceManager::GetAtlasTexture("roguelike", 6);
		cell.NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 6);
		cell.renderLayer = layer;
	}
	if (type == "WoodFloor")
	{
		cell.isWood = true;
		cell.Sprite = ResourceManager::GetAtlasTexture("roguelike", 34);
		cell.NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 34);
		cell.renderLayer = layer;
		//cell.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\wood_Diffuse.png");
		//cell.NormalMap = ResourceManager::LoadTexture("Resources\\Sprites\\Lighting\\wood_Normal2.png");
	}
	if (type == "Stone")
	{
		cell.isStone = true;
		cell.Sprite = ResourceManager::GetAtlasTexture("roguelike", 300);
		cell.NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 300);
		cell.renderLayer = layer;
	}


	if (type == "Water")
	{
		cell.isWater = true;
		cell.isWalkable = false;
		cell.Sprite = ResourceManager::GetAtlasTexture("roguelike", 0);
		cell.NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", 0);
		cell.renderLayer = ground_layer;
	}
	


	// LIGHTS
	if (type == "StreetLight")
	{
		LightSource streetLight(cell.getPosition(), LightSource::LightType::streetLight);
		streetLight.setSize(100, 50);
		if (cell.light == nullptr)
		{
			cell.light = streetLight.getPointer();
			cell.isWall = true;
		}
	}

	if (type == "CampFire")
	{
		LightSource streetLight(cell.getPosition(), LightSource::LightType::campfire);
		streetLight.setSize(50, 50);
		if (cell.light == nullptr)
		{
			cell.light = streetLight.getPointer();
			cell.isWall = true;
		}
	}


	// NPC houses
	if (type.compare(0, 8, "NPCHouse") == 0)
	{
		// Create house

		// load house from json
	}
}

int GetAtlasPositionFromOrientation(Cell::Orientation orient)
{
	switch (orient)
	{
	default:
		break;

	case Cell::Orientation::topLeft:
		return 0;
		break;
	case Cell::Orientation::topMiddle:
		return 1;
		break;
	case Cell::Orientation::topRight:
		return 2;
		break;
	case Cell::Orientation::middleLeft:
		return 7;
		break;

	case Cell::Orientation::middle:
		return 8;
		break;

	case Cell::Orientation::middleRight:
		return 9;
		break;

	case Cell::Orientation::bottomLeft:
		return 14;
		break;

	case Cell::Orientation::bottomMiddle:
		return 15;
		break;

	case Cell::Orientation::bottomRight:
		return 16;
		break;
	case Cell::Orientation::alone:
		return 58;
		break;

	case Cell::Orientation::inv_topLeft:
		return 3;
		break;
	case Cell::Orientation::inv_topRight:
		return 5;
		break;

	case Cell::Orientation::inv_bottomLeft:
		return 17;
		break;
	case Cell::Orientation::inv_bottomRight:
		return 19;
		break;

	}
}

void AssignLayer(Cell& cell, std::string textureName, int layer)
{
	if (layer == 0) // Set the ground sprite
	{
		cell.Sprite = ResourceManager::GetAtlasTexture(textureName, GetAtlasPositionFromOrientation(cell.orientation));
		cell.NormalMap = ResourceManager::GetAtlasTexture(textureName + "_normal", GetAtlasPositionFromOrientation(cell.orientation));
		cell.renderLayer = 0;
	}
	else
	{
		cell.layerdSprite = ResourceManager::GetAtlasTexture(textureName, GetAtlasPositionFromOrientation(cell.orientation));
		cell.layerdSprite_normal = ResourceManager::GetAtlasTexture(textureName + "_normal", GetAtlasPositionFromOrientation(cell.orientation));
		cell.renderLayer = 1;
	}
}
void CellAssignment::AssignCellFromType(Cell& cell, int layer)
{
	switch (cell.groundType)
	{
	default:
		break;
	case Cell::GroundType::spring_grass:
		AssignLayer(cell, "spring_grass_light", layer);
		break;
	case Cell::GroundType::spring_dirt:
		AssignLayer(cell, "spring_dirt_1", layer);
		break;
	case Cell::GroundType::spring_water:
		AssignLayer(cell, "spring_water", layer);
		break;
	}
}

