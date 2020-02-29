#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
	inventoryTimer.start();
}


UserInput::~UserInput()
{
}



void UserInput::HandleUserInput(GL_Renderer& renderer, Player& player, GameSettings& gameSettings, GameUI& UI)
{
	//SDL_JoystickEventState(SDL_ENABLE);
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			gameSettings.running = false;
		}
		//Mouse wheel
		switch (ev.type)
		{
		case SDL_MOUSEWHEEL:  /* Handle Mousewheel Motion */
			if (ev.wheel.x < 0)
			{
				std::cout << "MOUSE : WHEEL LEFT" << std::endl;
			}
			else if (ev.wheel.x > 0)
			{
				std::cout << "MOUSE : WHEEL RIGHT" << std::endl;
			}
			if (ev.wheel.y < 0)
			{
				UI.toolbar.setToolbarSelection(UI.toolbar.getToolbarSelection() + 1);
			}
			else if (ev.wheel.y > 0)
			{
				UI.toolbar.setToolbarSelection(UI.toolbar.getToolbarSelection() - 1);
			}
			break;

		case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
			//std::cout << ev.jaxis.which << std::endl;
			if (ev.jaxis.axis == 0)
			{
				if (ev.jaxis.value < 0)
					player.setX(player.getX() - player.getSpeed());
				else if (ev.jaxis.value > 0)
					player.setX(player.getX() + player.getSpeed());
			}

			else if (ev.jaxis.axis == 1)
			{
				if (ev.jaxis.value < 0)
					player.setY(player.getY() - player.getSpeed());
				else if (ev.jaxis.value > 0)
					player.setY(player.getY() + player.getSpeed());
			}
			break;
		}
	}

	// Keyboard Input
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{

	}

	// Set the players speed
	float deltaTime = gameSettings.deltaTime * 0.01;
	//player.setVelocity(player.getSpeed() * deltaTime, player.getSpeed() * deltaTime);



	playerChunkPos = player.chunkPos;
	playercellPos = player.cellPos;
	/////////// PLAYER MOVEMENT ////////////
	//Diagonal movement
	if (state[SDL_SCANCODE_LSHIFT])
	{
		player.setSpeed(player.getRunSpeed());
	}
	else
		player.setSpeed(player.getWalkSpeed());
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		//player.setTargetRotation(225);
		player.setTargetRotation(270);
		player.setPlayerMoving(true);
		
		player.Move(Player::MovementDirection::right_up);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		//player.setTargetRotation(135);
		player.setTargetRotation(90);
		player.setPlayerMoving(true);

		player.Move(Player::MovementDirection::left_up);

	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(-45);
		player.setTargetRotation(270);

		player.Move(Player::MovementDirection::right_down);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(45);
		player.setTargetRotation(90);

		player.Move(Player::MovementDirection::left_down);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(0);

		player.Move(Player::MovementDirection::down);
	}
	else if (state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(90);

		player.Move(Player::MovementDirection::left);

	}
	else if (state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(270);
		player.Move(Player::MovementDirection::right);
	}
	else if (state[SDL_SCANCODE_W])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(180);

		player.Move(Player::MovementDirection::up);
	}
	else
	{
		//player.setSpeed(0);
		player.setPlayerMoving(false);
		//player.setTargetRotation(0);
	}

	int x, y;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{

	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ACTION BAR
	if (state[SDL_SCANCODE_0])
		UI.toolbar.setToolbarSelection(10);
	else if (state[SDL_SCANCODE_1])
		UI.toolbar.setToolbarSelection(0);
	else if (state[SDL_SCANCODE_2])
		UI.toolbar.setToolbarSelection(1);
	else if (state[SDL_SCANCODE_3])
		UI.toolbar.setToolbarSelection(2);
	else if (state[SDL_SCANCODE_4])
		UI.toolbar.setToolbarSelection(3);
	else if (state[SDL_SCANCODE_5])
		UI.toolbar.setToolbarSelection(4);
	else if (state[SDL_SCANCODE_6])
		UI.toolbar.setToolbarSelection(5);
	else if (state[SDL_SCANCODE_7])
		UI.toolbar.setToolbarSelection(6);
	else if (state[SDL_SCANCODE_8])
		UI.toolbar.setToolbarSelection(7);



	if (state[SDL_SCANCODE_RIGHT])
	{
		UI.toolbar.setToolbarSelection(UI.toolbar.getToolbarSelection() + 1);
	}
	if (state[SDL_SCANCODE_DOWN])
	{


	}

	if (state[SDL_SCANCODE_LEFT])
	{
		UI.toolbar.setToolbarSelection(UI.toolbar.getToolbarSelection() - 1);
	}
	if (state[SDL_SCANCODE_UP])
	{
		player.setSpeed(player.getSpeed() + 1.0);
	}

	// Set cell size
	if (state[SDL_SCANCODE_PAGEUP])
	{
		LavenderSeeds ls;
		player.inventory.add(ls.getSharedPointer());
		//level.setCellSize(level.getCellSize() + 1);
	}



	if (state[SDL_SCANCODE_F])
	{
		player.pressingUseKey = true;
	}
	else
		player.pressingUseKey = false;

	if (state[SDL_SCANCODE_C])
	{

		if (inventoryTimer.getTicks() > inventoryTimeout)
		{
			if (!UI.characterWindow.isOpen)
			{
				UI.characterWindow.isOpen = true;
				UI.characterWindow.window.isOpen = true;
				UI.characterWindow.window.itemSelection.isOpen = true;
			}
			else
			{
				UI.characterWindow.isOpen = false;
				UI.characterWindow.window.isOpen = false;
				UI.characterWindow.window.itemSelection.isOpen = false;
			}
		}
		inventoryTimer.restart();
	}

	if (state[SDL_SCANCODE_I])
	{
		if (!craftingTimer.isStarted())
			craftingTimer.start();
	}

}