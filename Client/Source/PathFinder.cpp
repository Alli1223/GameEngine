#include "stdafx.h"
#include "PathFinder.h"
#include <future>

double euclideanDistance(const Point& a, const Point& b)
{
	double dx = a.getX() - a.getY();
	double dy = b.getX() - b.getY();
	//pythagoras(sp)
	double dist = 0.0;

	dist = pow(dx, 2) + pow(dy, 2);
	dist = sqrt(dist);
	
	return dist;
}

void Pathfinder::addToClosedSet(std::shared_ptr<Node> node)
{
	node->status = NodeStatus::Closed;
}

void Pathfinder::addToOpenSet(std::shared_ptr<Node> node)
{
	node->status = NodeStatus::Open;
}

std::vector<std::shared_ptr<Node>> Pathfinder::getNeighbours(std::shared_ptr<Node> node)
{
	std::vector<std::shared_ptr<Node>> result;
	// If the node is within the level
	try {
		if (node->point.getX() - 1 >= 0 && node->point.getX() + 1 < searchSize)
		{
			if (node->point.getY() - 1 >= 0 && node->point.getY() + 1 < searchSize)
			{
				//left
				result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY()));
				//right
				result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY()));
				//up
				result.push_back(getOrCreateNode(node->point.getX(), node->point.getY() - 1));
				//down
				result.push_back(getOrCreateNode(node->point.getX(), node->point.getY() + 1));

				// Diagonal paths
				if (diagonalPaths)
				{
					result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY() - 1));
					result.push_back(getOrCreateNode(node->point.getX() - 1, node->point.getY() + 1));
					result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY() - 1));
					result.push_back(getOrCreateNode(node->point.getX() + 1, node->point.getY() + 1));
				}
			}
		}
		return result;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}


std::shared_ptr<Node> Pathfinder::getOrCreateNode(int x, int y)
{
	if (x < nodes.size() && y < nodes[0].size())
	{

		auto result = nodes[x][y];
		if (!result)
		{
			result = std::make_shared<Node>(x, y);
			nodes[x][y] = result;
		}

		return result;
	}
}

std::shared_ptr<Node> Pathfinder::getOrCreateNode(const Point& point)
{
	return getOrCreateNode(point.getX(), point.getY());
}

bool Pathfinder::isInClosedSet(Point& point)
{
	auto node = nodes[point.getX()][point.getY()];
	return node != nullptr && node->status == NodeStatus::Closed;
}

std::shared_ptr<Node> Pathfinder::getOpenSetElementWithLowestScore()
{
	std::shared_ptr<Node> result = nullptr;
	double lowestFScore = 1e10;

	for (auto column : nodes)
	{
		for (auto node : column)
		{
			if (node != nullptr && node->status == NodeStatus::Open)
			{
				double f = node->g + node->h;
				if (result == nullptr || f < lowestFScore)
				{
					result = node;
					lowestFScore = f;
				}
			}
		}
	}

	return result;
}

std::vector<std::future< std::vector<glm::ivec2>>> paths; // List of pathfinding threads
//std::vector<glm::ivec2> Pathfinder::findPathThread(World& world, ivec2 startp, ivec2 goalp, bool isBuilding)
//{
//	// Create the thread
//
//	if (!computingPath)
//	{
//		if (!isBuilding)
//		{
//			auto futurePath = std::async(&Pathfinder::findPathInfiniWorld, this, world, startp, goalp);
//
//			// Erase previous path
//			if (id != -1)
//			{
//				if (!paths[id].valid())
//					paths.erase(paths.begin() + id);
//			}
//			// Add to list of pathfinding threads	
//			id = paths.size();
//			paths.push_back(std::move(futurePath));
//			computingPath = true;
//		}
//		// Find path in a finite grid
//		else
//		{
//			auto futurePath = std::async(&Pathfinder::findPathGrid, this, world.playerShop.tiles, startp, goalp);
//
//			// Erase previous path
//			if (id != -1)
//			{
//				if (!paths[id].valid())
//					paths.erase(paths.begin() + id);
//			}
//			// Add to list of pathfinding threads	
//			id = paths.size();
//			paths.push_back(std::move(futurePath));
//			computingPath = true;
//		}
//	}
//		
//	
//	// If the path has finished computing
//	if (paths[id].valid() && computingPath)
//		if (paths[id].wait_for(std::chrono::seconds(0)) == std::future_status::ready) // return the path
//		{
//			auto res1 = paths[id].get();
//			Path = res1;
//			computingPath = false;
//			return Path;
//		}
//
//
//	std::vector<ivec2> empty;
//	return empty;
//}

std::vector<glm::ivec2> Pathfinder::findPathThread(std::vector<std::vector<std::shared_ptr<Cell>>> tiles, ivec2 startp, ivec2 goalp)
{
	searchSize = 5;
	// Create the thread
	if (!computingPath)
	{
		auto futurePath = std::async(&Pathfinder::findPathGrid, this, tiles, startp, goalp);

		// Erase previous path
		if (id != -1)
		{
			if (!paths[id].valid())
				paths.erase(paths.begin() + id);
		}
		// Add to list of pathfinding threads	
		id = paths.size();
		paths.push_back(std::move(futurePath));
		computingPath = true;

	}


	// If the path has finished computing
	if (paths[id].valid() && computingPath)
		if (paths[id].wait_for(std::chrono::seconds(0)) == std::future_status::ready) // return the path
		{
			auto res1 = paths[id].get();
			Path = res1;
			computingPath = false;
			return Path;
		}


	std::vector<ivec2> empty;
	return empty;
}

//std::vector<glm::ivec2> Pathfinder::findPathInfiniWorld(World& world, ivec2 startp, ivec2 goalp)
//{
//	Point start;
//	Point goal;
//	goal.setPosition(goalp.x, goalp.y);
//	start.setPosition(startp.x, startp.y);
//
//	// Clear all the node for fresh pathfind
//	nodes.clear();
//
//	std::cout << "Computing Path" << std::endl;
//	std::cout << "First Pos: " << start.getX() << "," << start.getY() << " End: " << goal.getX() << "," << goal.getY() << std::endl;
//	// IF the start and end are accessable
//	//if (world.GetCell(start.getX(), start.getY())->isWalkable && world.GetCell(goal.getX(), goal.getY())->isWalkable)
//	{
//
//		//start and end offset
//		glm::ivec2 cellPos;
//		startNode = start;
//
//		if (true)
//		{
//			// Set offset to make path above 0
//			if (goal.getX() < 0)
//			{
//				offsetPath = true;
//				offset.x = (goal.getX() * -1);
//			}
//			if (goal.getY() < 0)
//			{
//				offsetPath = true;
//				offset.y = (goal.getY() * -1);
//			}
//
//
//			if (start.getX() < 0 && offset.x < (start.getX() * -1))
//			{
//				offset.x += (start.getX() * -1);
//				offsetPath = true;
//			}
//
//			if (start.getY() < 0 && offset.y < (start.getY() * -1))
//			{
//				offsetPath = true;
//				offset.y += (start.getY() * -1);
//			}
//		}
//
//		//offset += euclideanDistance(start, goal) * 2;
//		
//		if (offsetPath)
//			offset += 1;
//
//
//		start.setPosition(start.getX() + offset.x, start.getY() + offset.y);
//		goal.setPosition(goal.getX() + offset.x, goal.getY() + offset.y);
//		//startNode = start;
//
//		//change searchSize based on distance between target
//		searchSize = euclideanDistance(start, goal) * 2;
//		std::cout << "SearchSize: " << searchSize << std::endl;
//		std::cout << "Second Pos: " << start.getX() << "," << start.getY() << " End: " << goal.getX() << "," << goal.getY() << std::endl;
//		if (searchSize <= 5)
//			searchSize = 10;
//		
//		// Create nodes for every cell in the grid
//		for (int x = 0; x < searchSize; x++)
//		{
//			nodes.push_back(std::vector<std::shared_ptr<Node>>(searchSize, nullptr));
//		}
//
//
//
//		auto startNode = getOrCreateNode(start);
//		if (startNode != nullptr)
//		{
//			startNode->g = 0;
//			startNode->h = euclideanDistance(start, goal);
//			startNode->cameFrom = nullptr;
//			addToOpenSet(startNode);
//
//
//			// Chooses the best neighbour cell to move to
//			while (auto currentNode = getOpenSetElementWithLowestScore())
//			{
//				//if the current cell is the goal, make the path
//				if (currentNode->point.getX() == goal.getX() && currentNode->point.getY() == goal.getY())
//				{
//					//if (StringPullPath)
//					//	return StringPulling(reconstructPath(currentNode), world);
//					//else
//						return reconstructPath(currentNode);
//				}
//
//				addToClosedSet(currentNode);
//
//				// Loops through each of the neighbours
//				for each (auto neighbour in getNeighbours(currentNode))
//				{
//					cellPos.x = neighbour->point.getX() - offset.x, cellPos.y = neighbour->point.getY() - offset.y;
//					// If the cell is walkable
//					//if(world.GetCell(cellPos.x, cellPos.y)->isWalkable)
//						if (!isInClosedSet(neighbour->point))
//						{
//
//							double gTentative = currentNode->g + euclideanDistance(neighbour->point, goal);
//
//							if (neighbour->status != NodeStatus::Open || gTentative < neighbour->g)
//							{
//								neighbour->g = gTentative;
//								neighbour->h = euclideanDistance(neighbour->point, goal);
//								neighbour->cameFrom = currentNode;
//
//
//								if (neighbour->status != NodeStatus::Open)
//								{
//									addToOpenSet(neighbour);
//								}
//							}
//						}
//				}
//			}
//		}
//	}
//	//Return empty path if there is no route
//	std::vector<ivec2> EmptyPath;
//	return EmptyPath;
//	//throw PathfinderError();
//}
std::vector<glm::ivec2> Pathfinder::findPathGrid(std::vector<std::vector<std::shared_ptr<Cell>>> tiles, ivec2 startp, ivec2 goalp)
{
	Point start;
	Point goal;
	goal.setPosition(goalp.x, goalp.y);
	start.setPosition(startp.x, startp.y);

	// Clear all the node for fresh pathfind
	nodes.clear();


	std::cout << "Start Pos: " << start.getX() << "," << start.getY() << " End: " << goal.getX() << "," << goal.getY() << std::endl;
	// IF the start and end are accessable
	//if (world.GetCell(start.getX(), start.getY())->isWalkable && world.GetCell(goal.getX(), goal.getY())->isWalkable)
	try
	{

		//start and end offset
		glm::ivec2 cellPos;
		startNode = start;

		//offset += euclideanDistance(start, goal) * 2;



		start.setPosition(start.getX() + offset.x, start.getY() + offset.y);
		goal.setPosition(goal.getX() + offset.x, goal.getY() + offset.y);
		//startNode = start;

		//change searchSize based on distance between target
		//searchSize = euclideanDistance(start, goal) * 2;
		//std::cout << "SearchSize: " << searchSize << std::endl;
		//std::cout << "Second Pos: " << start.getX() << "," << start.getY() << " End: " << goal.getX() << "," << goal.getY() << std::endl;
		searchSize = tiles.size();

		// Create nodes for every cell in the grid
		for (int x = 0; x < searchSize; x++)
		{
			nodes.push_back(std::vector<std::shared_ptr<Node>>(searchSize, nullptr));
		}



		auto startNode = getOrCreateNode(start);
		if (startNode != nullptr)
		{
			startNode->g = 0;
			startNode->h = euclideanDistance(start, goal);
			startNode->cameFrom = nullptr;
			addToOpenSet(startNode);


			// Chooses the best neighbour cell to move to
			while (auto currentNode = getOpenSetElementWithLowestScore())
			{
				//if the current cell is the goal, make the path
				if (currentNode->point.getX() == goal.getX() && currentNode->point.getY() == goal.getY())
				{
					//if (StringPullPath)
					//	return StringPulling(reconstructPath(currentNode), world);
					//else
					return reconstructPath(currentNode);
				}

				addToClosedSet(currentNode);

				// Loops through each of the neighbours
				for each (auto neighbour in getNeighbours(currentNode))
				{
					cellPos.x = neighbour->point.getX(), cellPos.y = neighbour->point.getY();
					// If the cell is walkable
					if (tiles[cellPos.x][cellPos.y]->isWalkable)
						if (!isInClosedSet(neighbour->point))
						{

							double gTentative = currentNode->g + euclideanDistance(neighbour->point, goal);

							if (neighbour->status != NodeStatus::Open || gTentative < neighbour->g)
							{
								neighbour->g = gTentative;
								neighbour->h = euclideanDistance(neighbour->point, goal);
								neighbour->cameFrom = currentNode;


								if (neighbour->status != NodeStatus::Open)
								{
									addToOpenSet(neighbour);
								}
							}
						}
				}
			}
		}


		//Return empty path if there is no route
		std::vector<ivec2> EmptyPath;
		return EmptyPath;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		std::vector<ivec2> EmptyPath;
		return EmptyPath;
	}
	//throw PathfinderError();
}

std::vector<glm::ivec2> Pathfinder::reconstructPath(std::shared_ptr<Node> goalNode)
{
	std::vector<glm::ivec2> result;
	// Goes back through the path and reconstruct it and then return the result
	for (auto currentNode = goalNode; currentNode; currentNode = currentNode->cameFrom)
	{
		// If the path is offset, reset it
		if(offsetPath)
			currentNode->point.setPosition(currentNode->point.getX() - offset.x - 1, currentNode->point.getY() - offset.y - 1);
		result.insert(result.begin(), { currentNode->point.getX(), currentNode->point.getY() });
	}
	Path = result;
	std::cout << "PathSize: " << result.size() << std::endl;
	return result;
}

std::vector<Point> Pathfinder::StringPulling(std::vector<Point> path, World& level)
{
	int i = 0;
	while (i + 2 < path.size())
	{
		if (isPathObsructed(level, path[i], path[i + 2]))
			path.erase(path.begin() + i + 1);
		else
			i++;
	}
	path.shrink_to_fit();
	return path;
}

// Returns false if is obstructed
bool Pathfinder::isPathObsructed(World& level, Point firstPoint, Point secondPoint)
{
	float x1 = firstPoint.getX();
	float y1 = firstPoint.getY();
	float x2 = secondPoint.getX();
	float y2 = secondPoint.getY();

	// Bresenham's line algorithm copied and modified from internet
	//Link from source (http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B) Date accessed: 07.03.2017
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<maxX; x++)
	{
		if (steep)
		{
			//if (level.tiles[y][x]->isWalkable == false)
			//	return false;

		}
		else
		{
			//if (level.tiles[x][y]->isWalkable == false)
			//	return false;

		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	return true;
}

/*
void Pathfinder::drawPath(std::vector<Point>& path, SDL_Renderer* renderer, Camera& camera, World& level)
{
	// Start at the start point
	int lastX = 0;
	int lastY = 0;
	int cellSize = level.InfiniWorld.getCellSize();
	// tileSize / 2 is added to all coordinates to put them in the centre of the tile

	lastX = (path[0].getX() * cellSize + cellSize / 2) - camera.getX();
	lastY = (path[0].getY() * cellSize + cellSize / 2) - camera.getY();

	if (debugPathfinderArea)
	{

		SDL_Rect area;
		area.x = startNode.getX() - (offset.x * cellSize);
		area.y = startNode.getY() - (offset.y * cellSize);
		area.x -= camera.getX();
		area.y -= camera.getY();

		area.w = nodes.size() * cellSize;
		area.h = nodes[0].size() * cellSize;

		SDL_RenderDrawRect(renderer, &area);
		/*
		for (auto colums : nodes)
			for (auto node : colums)
			{
				SDL_Rect cell;

				getOrCreateNode(node->point);
				cell.x = node->point.getX();
				cell.y = node->point.getY();
				cell.w = cellSize;
				cell.h = cellSize;
				SDL_RenderDrawRect(renderer, &cell);
			}
			
	}

	// Step through the path
	for (const Point& point : path)
	{
		int nextX = point.getX() * cellSize + cellSize / 2;
		int nextY = point.getY() * cellSize + cellSize / 2;


		nextX -= camera.getX();
		nextY -= camera.getY();

		SDL_RenderDrawLine(renderer, lastX, lastY, nextX, nextY);
		lastX = nextX;
		lastY = nextY;
	}
}
*/