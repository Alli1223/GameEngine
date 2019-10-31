#pragma once
#include "Villager.h"
class Shopkeeper : public Villager
{
public:
	//! Constructor
	Shopkeeper::Shopkeeper();
	//! Destructor
	Shopkeeper::~Shopkeeper();

	std::shared_ptr<NPC> getSharedPointer();

	void Update();

};

