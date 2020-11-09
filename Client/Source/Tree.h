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

	//! Render override
	void Render(GL_Renderer& renderer);

	//! Create physics override
	void CreatePhysics(b2World* world);

	//! Get a shared pointer to this object
	std::shared_ptr<Item> getSharedPointer();

protected:
	//! Tree leaves
	Texture2D Leaves;
	Texture2D LeavesNormal;
	vec3 leafColour;
	float leafTransp = 1.0f;

	//! Tree Stump
	Texture2D Stump;
	Texture2D StumpNormal;
	vec3 stumpColour;

	//! Tree Shadow
	Texture2D Shadow;
private:




	std::string itemName = "Tree";
	std::string itemDescription = "Tree Item";
};

