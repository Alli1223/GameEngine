#include "stdafx.h"
#include "Rendering.h"

//! Constructor that initalises all the texture file locations
Rendering::Rendering()

	//// Summer
	//summerAtlas(summerTerrainSpriteTextureLocation + "new_Summer_grass_1.png"),
	//
	//// Buildings
	//ShopBuilding("Resources\\Buildings\\PotionShop.png")
{	//
	//// Set other atlas stats
	//terrainAtlas.setTileSize(128);
	//terrainAtlas.setTileSize(16);
	//
	//summerAtlas.setTileSize(64);
	//summerAtlas.setTileWidth(6);
	//summerAtlas.setAtlasType(0);
	//// Set rogue atlas stats
	//roguelikeAtlas.setTileSize(16);
	//roguelikeAtlas.setAtlasType(1);
	//roguelikeAtlas.setTileWidth(56);
	//
	//cropsAtlas.setTileSize(32);
	//cropsAtlas.setTileWidth(8);
	//cropsAtlas.setAtlasType(0);

	ResourceManager::LoadAtlas("roguelike", rogueLikeAtlasTextureLocation + "roguelikeSheet_transparent.png", 56, 16);
	ResourceManager::LoadAtlas("roguelike_normal", rogueLikeAtlasTextureLocation + "roguelikeSheet_transparent_normal.png", 56, 16);

	ResourceManager::LoadAtlas("spring_dirt_1", springTerrainSpriteTextureLocation + "dirt_spring.png", 6, 63);
	ResourceManager::LoadAtlas("spring_dirt_2", springTerrainSpriteTextureLocation + "dirt_spring_2.png", 6, 63);
	ResourceManager::LoadAtlas("spring_grass_1", springTerrainSpriteTextureLocation + "spring_grass_1.png", 6, 63);
	ResourceManager::LoadAtlas("spring_grass_1_normal", springTerrainSpriteTextureLocation + "spring_grass_1_Normal.png", 6, 63);
	ResourceManager::LoadAtlas("spring_grass_2", springTerrainSpriteTextureLocation + "spring_grass_2.png", 6, 63);
}

//! Destructor
Rendering::~Rendering()
{
}


void Rendering::renderCellsAroundObject(Level& level, int& x, int& y)
{
	int levelSize = level.tiles.size();


	// In one row
	if (x - 1 >= 0 && x + 1 < levelSize)
	{
		if (level.tiles[x][y]->isWater && level.tiles[x - 1][y]->isGrass)
		{
			level.tiles[x][y]->orientation = Cell::Orientation::middleLeft;
		}
		if (level.tiles[x][y]->isWater && level.tiles[x + 1][y]->isGrass)
		{
			level.tiles[x][y]->orientation = Cell::Orientation::middleRight;
		}

		// Center of Chunk
		if (y - 1 >= 0 && y + 1 < levelSize)
		{
			if(level.tiles[x][y]->isWater)
				level.tiles[x][y]->orientation = Cell::Orientation::middle;
			
			// Edges
			if (level.tiles[x][y]->isWater && level.tiles[x][y - 1]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::topMiddle;
			}
			if (level.tiles[x][y]->isWater && level.tiles[x - 1][y]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::middleLeft;
			}
			if (level.tiles[x][y]->isWater && level.tiles[x + 1][y]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::middleRight;
			}
			if (level.tiles[x][y]->isWater && level.tiles[x][y + 1]->isGrass)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::bottomMiddle;
			}

			// Top corners
			if (level.tiles[x][y]->isWater && !level.tiles[x - 1][y - 1]->isWater && !level.tiles[x][y - 1]->isWater && !level.tiles[x - 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::topLeft;
			}
			else if (level.tiles[x][y]->isWater && !level.tiles[x + 1][y - 1]->isWater && !level.tiles[x][y - 1]->isWater && !level.tiles[x + 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::topRight;
			}
			// Bottom corners
			else if (level.tiles[x][y]->isWater && !level.tiles[x - 1][y + 1]->isWater && !level.tiles[x][y + 1]->isWater && !level.tiles[x - 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::bottomLeft;
			}
			else if (level.tiles[x][y]->isWater && !level.tiles[x + 1][y + 1]->isWater && !level.tiles[x][y + 1]->isWater && !level.tiles[x + 1][y]->isWater)
			{
				level.tiles[x][y]->orientation = Cell::Orientation::bottomRight;
			}

			if(level.tiles[x][y]->isWater && level.tiles[x + 1][y]->isWater && level.tiles[x - 1][y]->isWater && level.tiles[x][y + 1]->isWater && level.tiles[x][y - 1]->isWater)
				level.tiles[x][y]->orientation = Cell::Orientation::middle;
		}
	}
	else if (y - 1 >= 0 && y + 1 < levelSize)
	{
		if (level.tiles[x][y]->isWater && level.tiles[x][y - 1]->isGrass)
			level.tiles[x][y]->orientation = Cell::Orientation::topMiddle;
		if (level.tiles[x][y]->isWater && level.tiles[x][y + 1]->isGrass)
			level.tiles[x][y]->orientation = Cell::Orientation::bottomMiddle;

	}
}

void Rendering::AssignTileSprites(std::vector<std::vector<std::shared_ptr<Cell>>>& tiles, int x ,int y)
{
	// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
	if (tiles[x][y]->isGrass)
	{

		//tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", grassID);
		//tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", grassID);
	}
	if (tiles[x][y]->isSand)
	{
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", sandID);
		tiles[x][y]->NormalMap = ResourceManager::GetAtlasTexture("roguelike_normal", sandID);
	}

	if (tiles[x][y]->isDirt)
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", dirtID);

	else if (tiles[x][y]->isLongGrass)
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", longGrass1);
	else if (tiles[x][y]->isSnow)
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", sandID);
	else if (tiles[x][y]->isRock)
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", rockID);
	else if (tiles[x][y]->isWood) {
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", 120);

	}
	else if (tiles[x][y]->isStone)
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", stoneID);
	if (tiles[x][y]->isTree)
		tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", treeBottom);

	if (tiles[x][y]->isWater)
	{
		// Code for ripples
		//sin(sqrt(pow(level.tiles[x][y]->getX(),2) + pow(level.tiles[x][y]->getY(),2)) + SDL_GetTicks() / 500) > 0)
		if (sin(tiles[x][y]->getX() + SDL_GetTicks() / 500) > 0)
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterID);
		else
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", water2ID);

		switch (tiles[x][y]->orientation)
		{
		case Cell::Orientation::topLeft:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterTopLeft);//AddToBatchRendering(waterTopLeft, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::topMiddle:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterTopMiddle);//AddToBatchRendering(waterTopMiddle, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::topRight:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterTopRight);//AddToBatchRendering(waterTopRight, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::middleLeft:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterMiddleLeft);//AddToBatchRendering(waterMiddleLeft, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::middle:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterID);//AddToBatchRendering(waterMiddle, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::middleRight:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterMiddleRight);//AddToBatchRendering(waterMiddleRight, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::bottomLeft:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterBottomLeft);//AddToBatchRendering(waterBottomLeft, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::bottomMiddle:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterBottomMiddle);//AddToBatchRendering(waterBottomMiddle, xPos, yPos, cellSize, ground);
			break;
		case Cell::Orientation::bottomRight:
			tiles[x][y]->Sprite = ResourceManager::GetAtlasTexture("roguelike", waterBottomRight);//AddToBatchRendering(waterBottomRight, xPos, yPos, cellSize, ground);
			break;
		}
	}
}



void Rendering::RenderLevel(Level& level, GameSettings& gameSettings, Player& player, GL_Renderer& renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = level.getCellSize();

	glm::vec2 renderArea = renderer.camera.getPosition();
	renderArea /= cellSize;

	// Don't access cells that can't exist
	if (renderArea.x <= 0)
		renderArea.x = 0;
	if (renderArea.y <= 0)
		renderArea.y = 0;


	for (int x = (int)renderArea.x; x < renderArea.x + level.cellsInWindowWidth + 1; x++)
		for (int y = (int)renderArea.y; y < renderArea.y + level.cellsInWindowHeight + 1; y++)
		{
			// Render object orientations
			//renderCellsAroundObject(level, x, y);

			//AssignTileSprites(level.tiles, x, y);

			level.tiles[x][y]->Render(renderer);
			
		}
}


//! Renders the chunks of cells
void Rendering::RenderObjects(World& world, GL_Renderer& renderer, Player& player, GameSettings& gameSettings)
{	

	world.Render(renderer);

	// Render player
	player.Render(renderer);	
	
}

void Rendering::RenderPlayer(SDL_Renderer* renderer, Player& player,  Level& level)
{
	//int x = player.getX() - camera.getX();
	//int y = player.getY() - camera.getY();
	//player.setPosition(x, y);
	//if (player.characterType == "Player")
		//characterTex.renderRotation(renderer, x, y, player.getSize(), player.getSize(), player.getRotation());
		//player.RenderPlayer(renderer);

}