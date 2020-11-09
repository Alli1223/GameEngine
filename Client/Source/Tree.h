#pragma once
#include "Item.h"
class Tree : public Item
{
public:
	//! Constructor
	Tree::Tree();
	Tree(json jsonData);

	//! Destructor
	Tree::~Tree();

	//! get Json
	virtual json GetJson();

	void Render(GL_Renderer& renderer);

	//! Get a shared pointer to this object
	std::shared_ptr<Item> getSharedPointer();

private:

	//! Tree leaves
	Texture2D Leaves;
	Texture2D LeavesNormal;


	std::string itemName = "Tree";
	std::string itemDescription = "Tree Item";
};

