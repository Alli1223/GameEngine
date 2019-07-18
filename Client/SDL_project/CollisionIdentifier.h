#pragma once
//! Used to store the object and type used in determining the objects that have collideded in box2D
class CollisionIdentifier
{
public:
	//! An object type for coverting from void*
	enum CollisionEntityTypes
	{
		empty,
		player,
		projectile,
		wall,
		enemy
	};
	CollisionEntityTypes entityType;

	// Can only construct with a type set
	CollisionIdentifier::CollisionIdentifier(CollisionEntityTypes type)
	{
		entityType = type;
	}

	//! Pointer to the object
	void* object = nullptr;
};
