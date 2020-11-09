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

protected:
	//! Tree leaves
	Texture2D Leaves;
	Texture2D LeavesNormal;

	//! Tree Stump
	Texture2D Stump;
	Texture2D StumpNormal;

	//! Tree Shadow
	Texture2D Shadow;
private:




	std::string itemName = "Tree";
	std::string itemDescription = "Tree Item";
};

