#include "stdafx.h"
#include "Shopkeeper.h"

Shopkeeper::Shopkeeper()
{
	characterType = "Shopkeeper";
	renderLayer = 3;
}

Shopkeeper::~Shopkeeper()
{
}

std::shared_ptr<NPC> Shopkeeper::getSharedPointer()
{
	if (thisptr == nullptr)
	{
		auto sharedNPCptr = std::make_shared<Shopkeeper>(*this);
		thisptr = sharedNPCptr;
		return std::shared_ptr<NPC>(thisptr);
	}
	else
	{
		return thisptr;
	}
}

void Shopkeeper::Update()
{
}
