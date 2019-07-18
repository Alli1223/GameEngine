// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "DungeonParty.h"

int main(int argc, char* args[])

{
	
	DungeonParty game;
	game.run();
	while (game.needsRestart)
	{
		DungeonParty game;
		game.run();
	}
	
	return 0;

}

