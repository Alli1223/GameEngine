#pragma once
#include <Box2D/Box2D.h>
#include "player.h"
#include "Projectile.h"
class CollisionListener : public b2ContactListener
{
public:
	CollisionListener();
	~CollisionListener();

	//! Contact between two objects
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);


};