#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
	//set random seed to seednumber
	srand(seed);

	Elevation.GenerateNoise(elevationSeed);
	ElevationLayerTwo.GenerateNoise(elevationSeed - 1234);
	ElevationLayerThree.GenerateNoise(elevationSeed + 1234);


	forrestNoise.GenerateNoise(forrestSeed);
	riverNoise.GenerateNoise(riverSeed);
	riverNoiseLayerTwo.GenerateNoise(riverSeed / 2);
}


ProceduralTerrain::~ProceduralTerrain()
{
}

std::shared_ptr<Cell> ProceduralTerrain::GetCell(int x, int y)
{
	if (levelptr != nullptr)
	{
		std::pair<int, int> val = { x,y };
		if (levelptr->count(val) == 0)
			return nullptr;
		else
			return levelptr->at(val);
	}
	else
		return nullptr;
}

void ProceduralTerrain::OrientateCells(std::shared_ptr<Cell> node, std::map<std::pair<int, int>, std::shared_ptr<Cell>>* level)
{
	levelptr = level;

	if (GetCell(node->getX() + 1, node->getY()) != nullptr)
		GetCell(node->getX() + 1, node->getY())->orientated = false;
	node->orientated = true;
		
	
	// Check that the cells exist before querying
	if (GetCell(node->getX() - 1, node->getY()) != nullptr && GetCell(node->getX() + 1, node->getY()) != nullptr && GetCell(node->getX(), node->getY() - 1) != nullptr && GetCell(node->getX(), node->getY() + 1) != nullptr)
	{
		if (GetCell(node->getX() - 1, node->getY() - 1) != nullptr && GetCell(node->getX() + 1, node->getY() - 1) != nullptr && GetCell(node->getX() - 1, node->getY() - 1) != nullptr && GetCell(node->getX() - 1, node->getY() + 1) != nullptr && GetCell(node->getX() + 1, node->getY() + 1) != nullptr)
		{
			// Default to none before setting
			node->SetOrientation(Cell::Orientation::none);

			// Top Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::topLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Top Middle //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::topMiddle);
										}
									}
								}
							}
						}
					}
				}
			}


			// Top Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::topRight);
										}
									}
								}
							}
						}
					}
				}
			}


			// Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::middleLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Middle //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::middle);
										}
									}
								}
							}
						}
					}
				}
			}

			// Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::middleRight);
										}
									}
								}
							}
						}
					}
				}
			}

			// Bottom Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							//if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::bottomLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Bottom Middle //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										//if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::bottomMiddle);
										}
									}
								}
							}
						}
					}
				}
			}

			// Bottom Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								//if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									//if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::bottomRight);
										}
									}
								}
							}
						}
					}
				}
			}

			// Alone //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType != node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType != node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType != node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType != node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::alone);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Top Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType != node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_topLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Top Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType != node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_topRight);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Bottom Left //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType == node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType != node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_bottomLeft);
										}
									}
								}
							}
						}
					}
				}
			}

			// Inverted Bottom Right //
			//left
			if (GetCell(node->getX() - 1, node->getY())->groundType == node->groundType)
			{ //Right
				if (GetCell(node->getX() + 1, node->getY())->groundType == node->groundType)
				{ //Up
					if (GetCell(node->getX(), node->getY() - 1)->groundType == node->groundType)
					{ //Down
						if (GetCell(node->getX(), node->getY() + 1)->groundType == node->groundType)
						{ //TopLeft
							if (GetCell(node->getX() - 1, node->getY() - 1)->groundType != node->groundType)
							{ //TopRight
								if (GetCell(node->getX() + 1, node->getY() - 1)->groundType == node->groundType)
								{ //BottomLeft
									if (GetCell(node->getX() - 1, node->getY() + 1)->groundType == node->groundType)
									{ //BottomRight
										if (GetCell(node->getX() + 1, node->getY() + 1)->groundType == node->groundType)
										{
											node->SetOrientation(Cell::Orientation::inv_bottomRight);
										}
									}
								}
							}
						}
					}
				}
			}

			node->AssignType(1);
		}
	}
}




void ProceduralTerrain::populateTerrain(std::vector<std::vector<std::shared_ptr<Cell>>>& chunk)
{
	//Renders all he cells
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[0].size(); y++)
		{
			//Generate the grass
			generateGround(chunk[x][y]);
		}
	}
	//Cant spawn random items because that will cause de-sync between clients

}

void ProceduralTerrain::populateTerrain(int x, int y)
{
	//Renders all he cells

	//Cant spawn random items because that will cause de-sync between clients

}


//TODO: Put all constant values in the headder
void ProceduralTerrain::generateGround(std::shared_ptr<Cell>& tile)
{
	float noiseX = tile->getX();
	float noiseY = tile->getY();

	// Layerd noise
	double terrainElevation = Elevation.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20.0;
	double terrainElevationTwo = ElevationLayerTwo.noise((double)noiseX / terrainNoiseOffest / 2.0, (double)noiseY / terrainNoiseOffest / 2.0, 0.0) * 20.0;
	double terrainElevationThree = ElevationLayerThree.noise((double)noiseX, (double)noiseY, 0.0) * 20.0;
	double sNoise = simNoise.noise(noiseX / 40, noiseY / 40);

	terrainElevation = sNoise + terrainElevationTwo + terrainElevation + terrainElevationThree + 2;
	double climate = sin(tile->getY() / 500.0);


	double fNoise = forrestNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20.0;
	fNoise += simNoise.noise(noiseX / forrestJaggedness, noiseY / forrestJaggedness);

	double gNoise = grassNoise.noise(noiseX / 15, noiseY / 15) + fNoise;
	double rNoise = (riverNoise.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0) + (riverNoiseLayerTwo.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0);
	rNoise += simNoise.noise(noiseX / riverBendyness, noiseY / riverBendyness);

	//set the cells terrain value
	tile->terrainElevationValue = terrainElevation;


	// TERRAIN NOISE
	if (terrainElevation >= -1.8 && terrainElevation <= 20.0)
	{
		tile->isGrass = true;
		std::string cell = "Grass";
		tile->AssignType(0, cell);
		if (terrainElevation >= 1.8 && terrainElevation < 9.0)
		{
			tile->isGrass = true;
			std::string cell = "Grass";
			tile->AssignType(0, cell);
			tile->SetGroundType(Cell::GroundType::spring_grass, 1);
		}
		if (terrainElevation >= 9.0 && terrainElevation < 12.0)
		{
			tile->isGrass = true;
			std::string cell = "Grass";
			tile->AssignType(0, cell);
			tile->SetGroundType(Cell::GroundType::spring_dirt, 1);
		}
	}
	else if (terrainElevation >= -2.3 && terrainElevation < -1.8)
	{
		std::string cell = "Dirt";
		tile->SetGroundType(Cell::GroundType::spring_dirt, 1);
		tile->isDirt = true;
		tile->isGrass = false;
		tile->isWater = false;
	}
	else if (terrainElevation < -2.3)
	{
		//std::string cell = "Water";
		//tile->SetGroundType(Cell::GroundType::spring_water,0);
		//tile->isWater = true;
		//tile->isWalkable = false;
	}
	else if (terrainElevation > 10.0 && terrainElevation < 20.0)
	{
		std::string cell = "Stone";
		tile->AssignType(0, cell);
		tile->isStone = true;
	}
	else if (terrainElevation > 20.0)
	{
		std::string cell = "Snow";
		tile->AssignType(0, cell);
		tile->isSnow = true;
	}

	// FORREST NOISE ///////////
	// If spawn something cool when the forrest value is greater than the max set ( the center of a forrest)
	//if (chunk->tile->isGrass && fNoise > 14.0 && rand() % numberOfTrees == 1)
	//{
	//	chunk->tile->isTree = true;
	//	chunk->tile->isWalkable = false;
	//}
	//else if (chunk->tile->isGrass && fNoise > 8.0 && fNoise < 12.0 && rand() % numberOfTrees == 1)
	//{
	//	chunk->tile->isTree = true;
	//	chunk->tile->isWalkable = false;
	//}
	//
	// Grass noise
	if (tile->isGrass && tile->orientation == Cell::Orientation::middle &&gNoise > 4.0 && gNoise < 10.0)
	{
		if (tile->groundType == Cell::GroundType::spring_grass)
		{
			int randSpawn = 26;
			tile->layerdSprite = ResourceManager::GetAtlasTexture("spring_grass_light", randSpawn);
			tile->layerdSprite_normal = ResourceManager::GetAtlasTexture("spring_grass_light_normal", randSpawn);
			tile->renderLayer = 1;
		}
	}
	if (tile->isGrass && tile->orientation == Cell::Orientation::middle && gNoise > 9.9 && gNoise < 15.0)
	{
		if (tile->groundType == Cell::GroundType::spring_grass)
		{
			int randSpawn = 40;
			tile->layerdSprite = ResourceManager::GetAtlasTexture("spring_grass_light", randSpawn);
			tile->layerdSprite_normal = ResourceManager::GetAtlasTexture("spring_grass_light_normal", randSpawn);
			tile->renderLayer = 1;
		}
	}


	// RIVER NOISE
	//if (rNoise > 0.5 && rNoise < 1.0)
	//{
	//	tile->isWater = true;
	//	tile->isGrass = false;
	//	tile->SetGroundType(Cell::GroundType::spring_water,1);
	//	tile->terrainElevationValue = -2.1;
	//}
	//
	//else if (rNoise >= 1.0 && rNoise < 1.3 || rNoise >= 0.3 && rNoise <= 0.5 && tile->isGrass)
	//{
	//	tile->isSand = true;
	//	tile->isGrass = false;
	//}

}

/*
void ProceduralTerrain::GenerateCellOrientations(std::shared_ptr<Chunk>& chunk, int& x, int& y)
{
	int chunkSize = chunk->getChunkSize();


	// In one row
	if (x - 1 >= 0 && x + 1 < chunkSize)
	{
		if (chunk->tile->isWater && chunk->tiles[x - 1][y]->isGrass)
		{
			chunk->tile->Orientation = Cell::Orientation::middleLeft;
		}
		if (chunk->tile->isWater && chunk->tiles[x + 1][y]->isGrass)
		{
			chunk->tile->Orientation = Cell::Orientation::middleLeft;
		}

		// Center of Chunk
		if (y - 1 >= 0 && y + 1 < chunkSize)
		{
			// Top Left
			if (chunk->tile->isWater && chunk->tiles[x - 1][y - 1]->isGrass && chunk->tiles[x][y - 1]->isGrass && chunk->tiles[x - 1][y]->isGrass)
			{
				chunk->tile->Orientation = Cell::Orientation::topLeft;
			}
			else if (chunk->tile->isWater && chunk->tiles[x][y - 1]->isGrass)
			{
				chunk->tile->Orientation = Cell::Orientation::topMiddle;
			}
			else if (chunk->tile->isWater && chunk->tiles[x + 1][y - 1]->isGrass && chunk->tiles[x][y - 1]->isGrass && chunk->tiles[x + 1][y]->isGrass)
			{
				chunk->tile->Orientation = Cell::Orientation::topRight;
			}
			else if (chunk->tile->isWater && chunk->tiles[x - 1][y]->isGrass)
			{
				chunk->tile->Orientation = Cell::Orientation::middleLeft;
			}
			else if (chunk->tile->isWater && chunk->tiles[x + 1][y]->isGrass)
			{
				chunk->tile->Orientation = Cell::Orientation::middleRight;
			}
			else if (chunk->tile->isWater && chunk->tiles[x][y + 1]->isGrass)
			{
				chunk->tile->Orientation = Cell::Orientation::bottomMiddle;
			}
			
		}
	}
	else if (y - 1 >= 0 && y + 1 < chunkSize)
	{
		if (chunk->tile->isWater && chunk->tiles[x][y - 1]->isGrass)
			chunk->tile->Orientation = Cell::Orientation::topMiddle;
		if (chunk->tile->isWater && chunk->tiles[x][y + 1]->isGrass)
			chunk->tile->Orientation = Cell::Orientation::topMiddle;

	}
	
}
*/