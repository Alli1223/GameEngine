#pragma once
#include "Item.h"
class Tree : public Item
{
public:
	//! Constructor
	Tree::Tree();

	//! Destructor
	Tree::~Tree();

	//! get Json
	virtual json GetJson();

	void Render(GL_Renderer& renderer);

	//! Get a shared pointer to this object
	std::shared_ptr<Item> getSharedPointer();

private:
	std::string itemName = "Tree";
	std::string itemDescription = "Tree Item";
};

