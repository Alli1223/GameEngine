#pragma once
#include "Character.h"
#include "PathFinder.h"
class NPC : public Character
{
public:
	//! Constructor
	NPC();
	//! Destructor
	~NPC();

	//! Whether a static or dynamic body
	b2BodyType bodyType;

	void Move(MovementDirection direction);
	
	virtual void Update(World& world);
	virtual void Update();

	//! Find Path
	virtual bool FindPath(glm::ivec2 start, glm::ivec2 end);

	// Get and Set NPC ID
	int getID() { return ID; }
	int setID(int newID) { return ID = newID; }

	//! Get a shared pointer to this object
	virtual std::shared_ptr<NPC> getSharedPointer();

	//! Reset Path if there have been any changes
	virtual void ResetPath();

	//! Whether the NPC is at home
	bool isAtHome = false;
	bool isSelected = false;

	//! Pointers to current level
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	
protected:

	//! Pathfinder path
	std::vector<glm::ivec2> path;
	std::shared_ptr<Pathfinder> pathfinder;


	std::shared_ptr<NPC> thisptr = nullptr;
	// ID for identifing this vilager
	int ID = -1;


	

};

