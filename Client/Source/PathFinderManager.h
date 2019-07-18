#pragma once
#include "World.h"
#include "PathFinder.h"
class PathFinderManager
{
public:
	PathFinderManager(World& world);
	~PathFinderManager();

	World* world;
	
	Pathfinder pathFinders;


	static std::vector<glm::ivec2> RequestPath(glm::ivec2 startPoint, glm::ivec2 goalPoint);
};

