// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "MainGame.h"

int main(int argc, char* args[])
{

	// Create new Game
	MainGame game;
	game.run();

	if(game.needsRestart)
	{
		MainGame game;
		game.run();
	}
	
	return 0;

}

