#pragma once
#include "Networkplayer.h"
#include "CollisionListener.h"
#include "NPC.h"

class Instance
{
public:
	//! Constructor
	Instance();
	Instance(json data);
	//! Deconstructor
	~Instance();

	virtual json GetJson();


	//! When player enters instance
	virtual void onEnter(Player& player);

	//! Instance setup
	virtual void InstanceSetup(Player& player);

	//! When player exits instace
	virtual void onExit(Player& player);

	//! Physics instance
	std::unique_ptr<b2World> I_Physics;

	//! Render
	virtual void Render(GL_Renderer& Renderer);

	//! Update
	virtual void Update();



	//! Player for instance
	Player I_player;

	//! List of players in instance
	std::vector<NetworkPlayer> networkPlayers;
	std::vector<std::shared_ptr<NPC>> npcs;

	//! Vector of cells that the user changes to send
	std::vector<std::shared_ptr<Cell>> updatedCells;

protected:

private:


};

