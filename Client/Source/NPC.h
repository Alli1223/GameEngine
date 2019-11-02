#pragma once
#include "Character.h"

class NPC : public Character
{
public:
	//! Constructor
	NPC();
	//! Destructor
	~NPC();

	b2BodyType bodyType;
	void Move(MovementDirection direction);

	virtual void Update(World& world);
	virtual void Update();

	// Get and Set NPC ID
	int getID() { return ID; }
	int setID(int newID) { return ID = newID; }

	//! Get a shared pointer to this object
	virtual std::shared_ptr<NPC> getSharedPointer();

	//! Whether the NPC is at home
	bool isAtHome = false;
	bool isSelected = false;
protected:

	std::shared_ptr<NPC> thisptr = nullptr;
	// ID for identifing this vilager
	int ID = -1;


	//! Body Textures
	Texture2D nakedBody;
	Texture2D hair;
	Texture2D eyes;
	Texture2D ears;
	Texture2D shadow;
	Texture2D top;
	Texture2D bottom;

	//! Default colours
	vec3 hairColour = { 255,255,255 };
	vec3 eyeColour = { 255,255,255 };
	vec3 topColour = { 255,255,255 };
	vec3 bottomColour = { 255,255,255 };
	vec3 bodyColour = { 255,224,189 };

	

};

