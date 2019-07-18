// SDL_project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SDL_project.h"
#include "UntitledGame.h"

int main(int argc, char* args[])

{
	
	UntitledGame game;
	game.run();
	while (game.needsRestart)
	{
		UntitledGame game;
		game.run();
	}
	
	return 0;

}

