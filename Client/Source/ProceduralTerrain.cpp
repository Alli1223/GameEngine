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




void ProceduralTerrain::populateTerrain(std::vector<std::vector<std::shared_ptr<Cell>>>& chunk)
{
	//Renders all he cells
	for (int x = 0; x < chunk.size(); x++)
	{
		for (int y = 0; y < chunk[0].size(); y++)
		{
			//Generate the grass
			generateGround(chunk, x, y);
		}
	}
	//Cant spawn random items because that will cause de-sync between clients

}

//TODO: Put all constant values in the headder
void ProceduralTerrain::generateGround(std::vector<std::vector<std::shared_ptr<Cell>>>& tiles, int x, int y)
{
	float noiseX = tiles[x][y]->getX();
	float noiseY = tiles[x][y]->getY();

	// Layerd noise
	double terrainElevation = Elevation.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20.0;
	double terrainElevationTwo = ElevationLayerTwo.noise((double)noiseX / terrainNoiseOffest / 2.0, (double)noiseY / terrainNoiseOffest / 2.0, 0.0) * 20.0;
	double terrainElevationThree = ElevationLayerThree.noise((double)noiseX, (double)noiseY, 0.0) * 20.0;
	double sNoise = simNoise.noise(noiseX / 40, noiseY / 40);

	terrainElevation = sNoise + terrainElevationTwo + terrainElevation + terrainElevationThree + 2;
	double climate = sin(tiles[x][y]->getY() / 500.0);


	double fNoise = forrestNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20.0;
	fNoise += simNoise.noise(noiseX / forrestJaggedness, noiseY / forrestJaggedness);

	double gNoise = grassNoise.noise(noiseX / 15, noiseY / 15) + fNoise;
	double rNoise = (riverNoise.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0) + (riverNoiseLayerTwo.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0);
	rNoise += simNoise.noise(noiseX / riverBendyness, noiseY / riverBendyness);

	//set the cells terrain value
	tiles[x][y]->terrainElevationValue = terrainElevation;


	// TERRAIN NOISE
	if (terrainElevation >= -1.8 && terrainElevation <= 20.0)
	{
		tiles[x][y]->isGrass = true;
		std::string tile = "Grass";
		tiles[x][y]->AssignType(0, tile);

	}
	else if (terrainElevation >= -2.3 && terrainElevation < -1.8)
	{
		std::string tile = "Sand";
		tiles[x][y]->AssignType(0, tile);
		tiles[x][y]->isSand = true;
		tiles[x][y]->isGrass = false;
		tiles[x][y]->isWater = false;
	}
	else if (terrainElevation < -2.3)
	{
		std::string tile = "Water";
		tiles[x][y]->AssignType(0, tile);
		tiles[x][y]->isWater = true;
		tiles[x][y]->isWalkable = false;
	}
	else if (terrainElevation > 10.0 && terrainElevation < 20.0)
	{
		std::string tile = "Stone";
		tiles[x][y]->AssignType(0, tile);
		tiles[x][y]->isStone = true;
	}
	else if (terrainElevation > 20.0)
	{
		std::string tile = "Snow";
		tiles[x][y]->AssignType(0, tile);
		tiles[x][y]->isSnow = true;
	}

	// FORREST NOISE ///////////
	// If spawn something cool when the forrest value is greater than the max set ( the center of a forrest)
	//if (chunk->tiles[x][y]->isGrass && fNoise > 14.0 && rand() % numberOfTrees == 1)
	//{
	//	chunk->tiles[x][y]->isTree = true;
	//	chunk->tiles[x][y]->isWalkable = false;
	//}
	//else if (chunk->tiles[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0 && rand() % numberOfTrees == 1)
	//{
	//	chunk->tiles[x][y]->isTree = true;
	//	chunk->tiles[x][y]->isWalkable = false;
	//}
	//
	//// Grass noise
	//if (chunk->tiles[x][y]->isGrass && gNoise > 4.0 && gNoise < 10.0)
	//{
	//	int randSpawn = rand() % 10;
	//	if (randSpawn == 0)
	//		chunk->tiles[x][y]->isLongGrass = true;
	//	else if(randSpawn == 3)
	//		chunk->tiles[x][y]->isLongGrass2 = true;
	//}


	// RIVER NOISE
	if (rNoise > 0.5 && rNoise < 1.0)
	{
		tiles[x][y]->isWater = true;
		tiles[x][y]->isGrass = false;
		tiles[x][y]->terrainElevationValue = -2.1;

	}

	else if (rNoise >= 1.0 && rNoise < 1.3 || rNoise >= 0.3 && rNoise <= 0.5 && tiles[x][y]->isGrass)
	{
		tiles[x][y]->isSand = true;
		tiles[x][y]->isGrass = false;
	}


}

/*
void ProceduralTerrain::GenerateCellOrientations(std::shared_ptr<Chunk>& chunk, int& x, int& y)
{
	int chunkSize = chunk->getChunkSize();


	// In one row
	if (x - 1 >= 0 && x + 1 < chunkSize)
	{
		if (chunk->tiles[x][y]->isWater && chunk->tiles[x - 1][y]->isGrass)
		{
			chunk->tiles[x][y]->orientation = Cell::orientation::middleLeft;
		}
		if (chunk->tiles[x][y]->isWater && chunk->tiles[x + 1][y]->isGrass)
		{
			chunk->tiles[x][y]->orientation = Cell::orientation::middleLeft;
		}

		// Center of Chunk
		if (y - 1 >= 0 && y + 1 < chunkSize)
		{
			// Top Left
			if (chunk->tiles[x][y]->isWater && chunk->tiles[x - 1][y - 1]->isGrass && chunk->tiles[x][y - 1]->isGrass && chunk->tiles[x - 1][y]->isGrass)
			{
				chunk->tiles[x][y]->orientation = Cell::orientation::topLeft;
			}
			else if (chunk->tiles[x][y]->isWater && chunk->tiles[x][y - 1]->isGrass)
			{
				chunk->tiles[x][y]->orientation = Cell::orientation::topMiddle;
			}
			else if (chunk->tiles[x][y]->isWater && chunk->tiles[x + 1][y - 1]->isGrass && chunk->tiles[x][y - 1]->isGrass && chunk->tiles[x + 1][y]->isGrass)
			{
				chunk->tiles[x][y]->orientation = Cell::orientation::topRight;
			}
			else if (chunk->tiles[x][y]->isWater && chunk->tiles[x - 1][y]->isGrass)
			{
				chunk->tiles[x][y]->orientation = Cell::orientation::middleLeft;
			}
			else if (chunk->tiles[x][y]->isWater && chunk->tiles[x + 1][y]->isGrass)
			{
				chunk->tiles[x][y]->orientation = Cell::orientation::middleRight;
			}
			else if (chunk->tiles[x][y]->isWater && chunk->tiles[x][y + 1]->isGrass)
			{
				chunk->tiles[x][y]->orientation = Cell::orientation::bottomMiddle;
			}
			
		}
	}
	else if (y - 1 >= 0 && y + 1 < chunkSize)
	{
		if (chunk->tiles[x][y]->isWater && chunk->tiles[x][y - 1]->isGrass)
			chunk->tiles[x][y]->orientation = Cell::orientation::topMiddle;
		if (chunk->tiles[x][y]->isWater && chunk->tiles[x][y + 1]->isGrass)
			chunk->tiles[x][y]->orientation = Cell::orientation::topMiddle;

	}
	
}
*/