#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::CharacterSelection(GameSettings& gameSettings, GL_Renderer& renderer, World& level, Player& player)
{
	existingPlayers = gameSettings.levelSaving.LoadPlayers();
	//! Create New
	//set ID to characterList size
	Button createNew("Create New");
	createNew.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\Plain_Button.png");
	createNew.setPosition({ renderer.camera.windowSize.x / 2, renderer.camera.windowSize.y - 200 });
	createNew.setSize({ 200,40 });
	createNew.setColour({ 200,100,50 });
	createNew.textColour = { 255,255,255 };

	//! Select Existing
	std::vector<Button> existingPlayerButtons;
	for (int i = 0; i < existingPlayers.size(); i++)
	{
		Button playerButton(std::to_string(existingPlayers[i].getID()), { renderer.camera.windowSize.x / 2, renderer.camera.windowSize.x / 10 + 50 * i }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, { 123,123,123 }, { 255,255,255 });
		existingPlayerButtons.push_back(playerButton);
	}




	while (displayMainMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayMainMenu = false;
			}
		}
		// Start render
		// Clear screen
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShowCursor(true);
		SDL_ShowCursor(SDL_ENABLE);

		
		// Render buttons
		for (int i = 0; i < existingPlayerButtons.size(); i++)
		{
			renderer.camera.SetPos(0,0);
			existingPlayerButtons[i].Render(renderer);
			existingPlayers[i].setSize(50, 50);
			existingPlayers[i].setRenderLayer(0);
			existingPlayers[i].setPosition({ existingPlayerButtons[i].getPosition().x + (existingPlayerButtons[i].getSize().x / 2.0f), existingPlayerButtons[i].getPosition().y });
			existingPlayers[i].Render(renderer);
			if (existingPlayerButtons[i].isPressed())
			{
				displayMainMenu = false;
				player = existingPlayers[i];
				player.setRenderLayer(3);
				break;
			}
		}

		createNew.Render(renderer);

		if (createNew.isPressed())
		{
			CharacterCustomisationMenu(gameSettings, renderer.camera, player, renderer, level);
			break;
		}

		SDL_GL_SwapWindow(window);
	}
}


void Menu::MainMenu(GameSettings& gameSettings, World& level, Camera& camera, Player& player, GL_Renderer& renderer, SDL_Window* window, SDL_GLContext& glContext)
{
	this->window = window;
	this->glContext = &glContext;
	// Create buttons
	//Button characterScreen("Character Customisation");
	//Button exit({ 50,25 }, { 100,50 }, ResourceManager::LoadTexture("Resources\\UI\\Background.png"), textColour);
	Button exit("Exit");
	exit.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\Plain_Button.png");
	exit.setPosition({ camera.windowSize.x / 2, camera.windowSize.y / 2 - 80 });
	exit.setSize({ 200,40 });
	exit.setColour({ 200,100,50 });
	exit.textColour = { 255,255,255 };

	Button play("Play");
	play.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\Plain_Button.png");
	play.setPosition({ camera.windowSize.x / 2, camera.windowSize.y / 2 });
	play.setSize({ 200,40 });
	play.setColour({ 200,100,50 });
	play.textColour = { 255,255,255 };


	// Scale mouse correctly depending on resolution
	menuCursorSize = gameSettings.WINDOW_WIDTH / 25;
	//bodyColourSlider.setColour(player.getBodyColour());
	gameSettings.gotoMainMenu = false;
	gameSettings.inGameMenu = false;
	// Display the menu screen

	while (displayMainMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayMainMenu = false;
			}
		}

		// Start render
		// Clear screen
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShowCursor(true);
		SDL_ShowCursor(SDL_ENABLE);

		// Render buttons
		exit.Render(renderer);
		play.Render(renderer);

		if (play.isPressed())
		{
			CharacterSelection(gameSettings, renderer, level, player);
			//CharacterCustomisationMenu(gameSettings, camera, player, renderer, level);
		}

		if (exit.isPressed())
		{
			gameSettings.running = false;
			break;
		}


		SDL_GL_SwapWindow(window);
	}
}


void Menu::CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, GL_Renderer& renderer, World& level)
{
	Player playerCreation;

	glm::vec3 textColour = { 255,255,255 };

	// Load player from file
	playerCreation = gameSettings.getPlayerFromSave();
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5, gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	playerCreation.CharacterClothes.body = Player::Clothing::femaleTop1;
	playerCreation.CharacterClothes.leg = Player::Clothing::femaleBottom2;
	playerCreation.setRenderLayer(0);
	player.setID(existingPlayers.size());

	/////// Organic customisation buttons //////

	int buttonSize = 50;
	int bSize2 = buttonSize * 2;
	int ObuttonsX = playerCreation.getX() - playerCreation.getSize().x;
	int ObuttonsY = playerCreation.getY() - buttonSize * 4;
	int CbuttonsX = playerCreation.getX() + playerCreation.getSize().x + bSize2;
	int CbuttonsY = playerCreation.getY() - buttonSize * 4;

	// Create buttons
	Button back("", { 100,100 }, "Resources\\UI\\Buttons\\NoButton.png", { 100,100 }, { 200,100,50 }, textColour);
	Button confirm("", { camera.windowSize.x - 200, camera.windowSize.y  - 50 }, "Resources\\UI\\Buttons\\Confirm.png", { 200,50 }, { 200,100,50 }, textColour);
	Button loadSave("Load Save", { camera.windowSize.x / 2, camera.windowSize.y / 2 + (camera.windowSize.y / 4) }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, { 200,100,50 }, textColour);


	// LEFT SIDE (ORGANIC)
	// Gender
	// Skin colour
	// Eye Type
	// Eye Colour
	int leftPosition1 = camera.windowSize.x / 2 - camera.windowSize.x / 4;
	int leftPosition2 = camera.windowSize.x / 2 - camera.windowSize.x / 4 - 100;
	glm::vec3 buttonColour = { 200,150,150 };

	// Genders
	Button femaleGender("", { playerCreation.getX() - leftPosition1, playerCreation.getY() - 100 }, "Resources\\UI\\Buttons\\FemaleButton.png", { 50,50 }, buttonColour, textColour);
	Button maleGender("", { playerCreation.getX() - leftPosition2, playerCreation.getY() - 100 }, "Resources\\UI\\Buttons\\MaleButton.png", { 50,50 }, buttonColour, textColour);
	// Colours
	//Types
	//Hair Type
	Button ChangeHairTypeL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, textColour);
	Button ChangeHairTypeR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, textColour);
	//Ear
	Button ChangeEarTypeL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, textColour);
	Button ChangeEarTypeR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, textColour);
	//Eye
	Button ChangeEyeTypeL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() + 100 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, textColour);
	Button ChangeEyeTypeR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() + 100 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, textColour);


	// Colours
	Button ChangeBodyColour("Body Colour", { playerCreation.getX() - leftPosition1 + 50, playerCreation.getY() + 200 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, textColour);
	Button ChangeEyeColour("Eye Colour", { playerCreation.getX() - leftPosition1 + 50, playerCreation.getY() + 250 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, textColour);
	Button ChangeHairColour("Hair Colour", { playerCreation.getX() - leftPosition1 + 50, playerCreation.getY() + 300 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, textColour);


	// Right Side ( CLOTHES)
	int rightPosition1 = camera.windowSize.x / 2 - camera.windowSize.x / 4 - 100;
	int rightPosition2 = camera.windowSize.x / 2 - camera.windowSize.x / 4;
	int rightPositionCenter = camera.windowSize.x / 2 - camera.windowSize.x / 4 - 50;

	//Top
	Button changeTopL("", { playerCreation.getX() + rightPosition1, playerCreation.getY() }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, textColour);
	Button changeTopR("", { playerCreation.getX() + rightPosition2, playerCreation.getY() }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, textColour);
	//Bottom
	Button changeBottomL("", { playerCreation.getX() + rightPosition1, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, textColour);
	Button changeBottomR("", { playerCreation.getX() + rightPosition2, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, textColour);
	//Colour
	Button ChangeTopColour("Top Colour", { playerCreation.getX() + rightPositionCenter, playerCreation.getY() + 200 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, textColour);
	Button ChangeBottomColour("Bottom Colour", { playerCreation.getX() + rightPositionCenter, playerCreation.getY() + 250 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, textColour);



	Button randomiseAll("Random", { camera.windowSize.x / 2, camera.windowSize.y - camera.windowSize.y / 3 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200, 50 }, buttonColour, textColour);




	while (displayCharacterMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			//getColourWheelvalue(renderer, mouseX, mouseY);
		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayCharacterMenu = false;
			}
		}

		// Start render
		// Clear screen
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);



		back.Render(renderer);
		confirm.Render(renderer);
		femaleGender.Render(renderer);
		maleGender.Render(renderer);
		//ChangeSkinColourL.Render(renderer);
		//ChangeSkinColourR.Render(renderer);
		//ChangeHairColourL.Render(renderer);
		//ChangeHairColourR.Render(renderer);
		//ChangeEyeColourL.Render(renderer);
		//ChangeEyeColourR.Render(renderer);
		ChangeHairTypeL.Render(renderer);
		ChangeHairTypeR.Render(renderer);
		ChangeEarTypeL.Render(renderer);
		ChangeEarTypeR.Render(renderer);
		ChangeEyeTypeL.Render(renderer);
		ChangeEyeTypeR.Render(renderer);
		
		ChangeBodyColour.Render(renderer);

		ChangeEyeColour.Render(renderer);
		ChangeHairColour.Render(renderer);

;

		changeTopL.Render(renderer);
		changeTopR.Render(renderer);

		changeBottomL.Render(renderer);
		changeBottomR.Render(renderer);

		ChangeTopColour.Render(renderer);
		ChangeBottomColour.Render(renderer);

		randomiseAll.Render(renderer);


		playerCreation.Render(renderer);


		if (back.isPressed())
		{
			gameSettings.running = false;
			break;
		}





		//randomiseAll.render(renderer, playerCreation.getX(), gameSettings.WINDOW_HEIGHT - buttonSize, buttonSize * 3, buttonSize);
		//
		//
		//
		//// BUTTON FUNCTIONALITY

		if (maleGender.isPressed())
			playerCreation.body.gender = Player::Body::Gender::male;
		if (femaleGender.isPressed())
			playerCreation.body.gender = Player::Body::Gender::female;
		
		// Change Ear buttons
		if (ChangeEarTypeL.isPressed())
		{
			changeEarType(playerCreation, false);
		}
		else if (ChangeEarTypeR.isPressed())
		{
			changeEarType(playerCreation, true);
		}
		
		// Change Eye buttons
		if (ChangeEyeTypeL.isPressed())
		{
			changeEyeType(playerCreation, false);
		}
		else if (ChangeEyeTypeR.isPressed())
		{
			changeEyeType(playerCreation, true);
		}
		
		// Change Hair buttons
		if (ChangeHairTypeL.isPressed())
		{
			changeHairType(playerCreation, false);
		}
		else if (ChangeHairTypeR.isPressed())
		{
			changeHairType(playerCreation, true);
		}
		
		
		
		
		// Button functionality
		//Legs
		if (changeBottomL.isPressed())
		{
			changeBottomType(playerCreation, false);
		}
		else if (changeBottomR.isPressed())
		{
			changeBottomType(playerCreation, true);
		}
		// Body
		if (changeTopL.isPressed())
		{
			changeTopType(playerCreation, false);
		}
		else if (changeTopR.isPressed())
		{
			changeTopType(playerCreation, true);
		}
		
		
		
		// Body Colour
		if (ChangeBodyColour.isPressed())
		{
			hairColourSlider.Disable();
			eyeColourSlider.Disable();
			topColourSlider.Disable();
			bottomColourSlider.Disable();
			if (bodyColourSlider.isEnabled())
				bodyColourSlider.Disable();
			else
				bodyColourSlider.Enable();
		
		}
		// Hair colour
		if (ChangeHairColour.isPressed())
		{
			bodyColourSlider.Disable();
			eyeColourSlider.Disable();
			topColourSlider.Disable();
			bottomColourSlider.Disable();
			if (hairColourSlider.isEnabled())
				hairColourSlider.Disable();
			else
				hairColourSlider.Enable();
		}
		// Eye colour
		if (ChangeEyeColour.isPressed())
		{
			hairColourSlider.Disable();
			bodyColourSlider.Disable();
			topColourSlider.Disable();
			bottomColourSlider.Disable();
			if (eyeColourSlider.isEnabled())
				eyeColourSlider.Disable();
			else
				eyeColourSlider.Enable();
		}
		
		// Clothes colours
		if (ChangeTopColour.isPressed())
		{
			hairColourSlider.Disable();
			bodyColourSlider.Disable();
			bottomColourSlider.Disable();
			eyeColourSlider.Disable();
			if (topColourSlider.isEnabled())
				topColourSlider.Disable();
			else
				topColourSlider.Enable();
		}
		if (ChangeBottomColour.isPressed())
		{
			hairColourSlider.Disable();
			bodyColourSlider.Disable();
			eyeColourSlider.Disable();
			topColourSlider.Disable();
			if (bottomColourSlider.isEnabled())
				bottomColourSlider.Disable();
			else
				bottomColourSlider.Enable();
		}
		// Random button
		if (randomiseAll.isPressed())
		{
			playerCreation.setHairColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setEyeColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setJacketColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setJeansColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setBodyColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.body.earType = Player::Body::EarType(rand() % 8);
			playerCreation.body.eyeType = Player::Body::EyeType(rand() % 13);
			playerCreation.body.hairType = Player::Body::HairType(rand() % 8);
		}
		
		
		
		// Colour slider object positions and functionality
		// body slider
		if (bodyColourSlider.isEnabled())
		{
			//ChangeBodyColour.getButtonBackgroundTexture().alterTextureColour(bodyColourSlider.getColour());
			bodyColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			bodyColourSlider.setWidth(360);
			bodyColourSlider.setHeight(50);
			bodyColourSlider.Render(renderer);
			playerCreation.setBodyColour(bodyColourSlider.getColour());
		}
		// hair slider
		if (hairColourSlider.isEnabled())
		{
			//ChangeHairColour.getButtonBackgroundTexture().alterTextureColour(hairColourSlider.getColour());
			hairColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			hairColourSlider.setWidth(360);
			hairColourSlider.setHeight(50);
			hairColourSlider.Render(renderer);
			playerCreation.setHairColour(hairColourSlider.getColour());
		}
		// eye slider
		if (eyeColourSlider.isEnabled())
		{
			//ChangeEyeColour.getButtonBackgroundTexture().alterTextureColour(eyeColourSlider.getColour());
			eyeColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			eyeColourSlider.setWidth(360);
			eyeColourSlider.setHeight(50);
			eyeColourSlider.Render(renderer);
			playerCreation.setEyeColour(eyeColourSlider.getColour());
		}
		
		// If top colour slider is enabled
		if (topColourSlider.isEnabled())
		{
			//ChangeTopColour.getButtonBackgroundTexture().alterTextureColour(topColourSlider.getColour());
			topColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			topColourSlider.setWidth(360);
			topColourSlider.setHeight(50);
			topColourSlider.Render(renderer);
			playerCreation.setTopColour(topColourSlider.getColour());
		}
		// if bottom colour slider is enabled
		if (bottomColourSlider.isEnabled())
		{
			//ChangeBottomColour.getButtonBackgroundTexture().alterTextureColour(bottomColourSlider.getColour());
			bottomColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			bottomColourSlider.setWidth(360);
			bottomColourSlider.setHeight(50);
			bottomColourSlider.Render(renderer);
			playerCreation.setBottomColour(bottomColourSlider.getColour());
		}
		
		//TODO: fix this
		// Render player
		//playerCreation.RenderPlayer(gl, camera);
		
		
		// Back button
		//back.render(renderer, 50, 150, 100, 50);
		if (back.isPressed())
		{
			displayCharacterMenu = false;
			return;
		}
		
		// Start
		//singleplayer.render(renderer, gameSettings.WINDOW_WIDTH / 2 + 200, gameSettings.WINDOW_HEIGHT - 100, buttonSize * 2, buttonSize);
		if (confirm.isPressed())
		{
			gameSettings.running = true;
			displayCharacterMenu = false;
			displayMainMenu = false;
		}
		
		//loadSave.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT - 100 - buttonSize * 2, buttonSize * 2, buttonSize);
		if (loadSave.isPressed())
		{
			displayCharacterMenu = false;
			//gameSettings.loadGameFromSave(level);
			player = gameSettings.getPlayerFromSave();
			displayMainMenu = false;
		}
		
		//rotateplayer.render(renderer, gameSettings.WINDOW_WIDTH / 2, playerCreation.getY() + playerCreation.getSize().x / 2 + buttonSize, buttonSize * 2, buttonSize);
		//if (rotateplayer.isPressed())
		//{
		//	int rotation = playerCreation.getTargetRotation() + 90;
		//	if (rotation > 360)
		//		rotation = 0;
		//	playerCreation.setTargetRotation(rotation);
		//}
		
		
		
		
		////Render the mouse cursor last
		//if (renderCursor)
		//	cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		//SDL_RenderPresent(renderer);



		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		SDL_GL_SwapWindow(window);

	//Only copy over the customsiation stuff
	//playerCreation.setSize(100);


	}
	player.CharacterClothes = playerCreation.CharacterClothes;
	player.setHairColour(playerCreation.gethairColour().r, playerCreation.gethairColour().g, playerCreation.gethairColour().b);
	player.setEyeColour(playerCreation.getEyeColour().r, playerCreation.getEyeColour().g, playerCreation.getEyeColour().b);
	player.setJacketColour(playerCreation.getJacketColour().r, playerCreation.getJacketColour().g, playerCreation.getJacketColour().b);
	player.setJeansColour(playerCreation.getJeansColour().r, playerCreation.getJeansColour().g, playerCreation.getJeansColour().b);
	player.body = playerCreation.body;
	player.setBodyColour(playerCreation.getBodyColour().r, playerCreation.getBodyColour().g, playerCreation.getBodyColour().b);
}

















	
void Menu::changeEarType(Player & player, bool increment)
{
	if (increment)
	{
		switch (player.body.earType)
		{
		case Player::Body::EarType::aquatic:
			player.body.earType = Player::Body::EarType::cat1;
			break;
		case Player::Body::EarType::cat1:
			player.body.earType = Player::Body::EarType::cat2;
			break;
		case Player::Body::EarType::cat2:
			player.body.earType = Player::Body::EarType::elf1;
			break;
		case Player::Body::EarType::elf1:
			player.body.earType = Player::Body::EarType::elf2;
			break;
		case Player::Body::EarType::elf2:
			player.body.earType = Player::Body::EarType::elf3;
			break;
		case Player::Body::EarType::elf3:
			player.body.earType = Player::Body::EarType::elf4;
			break;
		case Player::Body::EarType::elf4:
			player.body.earType = Player::Body::EarType::elf5;
			break;
		case Player::Body::EarType::elf5:
			player.body.earType = Player::Body::EarType::elf6;
			break;
		case Player::Body::EarType::elf6:
			player.body.earType = Player::Body::EarType::human;
			break;
		case Player::Body::EarType::human:
			player.body.earType = Player::Body::EarType::aquatic;
			break;
		}
	}
	else
		switch (player.body.earType)
		{
		case Player::Body::EarType::aquatic:
			player.body.earType = Player::Body::EarType::human;
			break;
		case Player::Body::EarType::human:
			player.body.earType = Player::Body::EarType::elf6;
			break;
		case Player::Body::EarType::elf6:
			player.body.earType = Player::Body::EarType::elf5;
			break;
		case Player::Body::EarType::elf5:
			player.body.earType = Player::Body::EarType::elf4;
			break;
		case Player::Body::EarType::elf4:
			player.body.earType = Player::Body::EarType::elf3;
			break;
		case Player::Body::EarType::elf3:
			player.body.earType = Player::Body::EarType::elf2;
			break;
		case Player::Body::EarType::elf2:
			player.body.earType = Player::Body::EarType::elf1;
			break;
		case Player::Body::EarType::elf1:
			player.body.earType = Player::Body::EarType::cat2;
			break;
		case Player::Body::EarType::cat2:
			player.body.earType = Player::Body::EarType::cat1;
			break;
		case Player::Body::EarType::cat1:
			player.body.earType = Player::Body::EarType::aquatic;
			break;
		}
}


void Menu::changeEyeType(Player & player, bool increment)
{
	if (increment)
	{
		switch (player.body.eyeType)
		{
		case Player::Body::EyeType::eye1:
			player.body.eyeType = Player::Body::EyeType::eye2;
			break;
		case Player::Body::EyeType::eye2:
			player.body.eyeType = Player::Body::EyeType::eye3;
			break;
		case Player::Body::EyeType::eye3:
			player.body.eyeType = Player::Body::EyeType::eye4;
			break;
		case Player::Body::EyeType::eye4:
			player.body.eyeType = Player::Body::EyeType::eye5;
			break;
		case Player::Body::EyeType::eye5:
			player.body.eyeType = Player::Body::EyeType::eye6;
			break;
		case Player::Body::EyeType::eye6:
			player.body.eyeType = Player::Body::EyeType::eye7;
			break;
		case Player::Body::EyeType::eye7:
			player.body.eyeType = Player::Body::EyeType::eye8;
			break;
		case Player::Body::EyeType::eye8:
			player.body.eyeType = Player::Body::EyeType::eye9;
			break;
		case Player::Body::EyeType::eye9:
			player.body.eyeType = Player::Body::EyeType::eye10;
			break;
		case Player::Body::EyeType::eye10:
			player.body.eyeType = Player::Body::EyeType::eye11;
			break;
		case Player::Body::EyeType::eye11:
			player.body.eyeType = Player::Body::EyeType::eye12;
			break;
		case Player::Body::EyeType::eye12:
			player.body.eyeType = Player::Body::EyeType::eye13;
			break;
		case Player::Body::EyeType::eye13:
			player.body.eyeType = Player::Body::EyeType::eye1;
			break;
		}
	}
	else
		switch (player.body.eyeType)
		{
		case Player::Body::EyeType::eye13:
			player.body.eyeType = Player::Body::EyeType::eye12;
			break;
		case Player::Body::EyeType::eye12:
			player.body.eyeType = Player::Body::EyeType::eye11;
			break;
		case Player::Body::EyeType::eye11:
			player.body.eyeType = Player::Body::EyeType::eye10;
			break;
		case Player::Body::EyeType::eye10:
			player.body.eyeType = Player::Body::EyeType::eye9;
			break;
		case Player::Body::EyeType::eye9:
			player.body.eyeType = Player::Body::EyeType::eye8;
			break;
		case Player::Body::EyeType::eye8:
			player.body.eyeType = Player::Body::EyeType::eye7;
			break;
		case Player::Body::EyeType::eye7:
			player.body.eyeType = Player::Body::EyeType::eye6;
			break;
		case Player::Body::EyeType::eye6:
			player.body.eyeType = Player::Body::EyeType::eye5;
			break;
		case Player::Body::EyeType::eye5:
			player.body.eyeType = Player::Body::EyeType::eye4;
			break;
		case Player::Body::EyeType::eye4:
			player.body.eyeType = Player::Body::EyeType::eye3;
			break;
		case Player::Body::EyeType::eye3:
			player.body.eyeType = Player::Body::EyeType::eye2;
			break;
		case Player::Body::EyeType::eye2:
			player.body.eyeType = Player::Body::EyeType::eye1;
			break;
		case Player::Body::EyeType::eye1:
			player.body.eyeType = Player::Body::EyeType::eye13;
			break;
		}
}


void Menu::changeHairType(Player & player, bool increment)
{
	if (increment)
	{
		switch (player.body.hairType)
		{
		case Player::Body::HairType::hair1:
			player.body.hairType = Player::Body::HairType::hair2;
			break;
		case Player::Body::HairType::hair2:
			player.body.hairType = Player::Body::HairType::hair3;
			break;
		case Player::Body::HairType::hair3:
			player.body.hairType = Player::Body::HairType::hair4;
			break;
		case Player::Body::HairType::hair4:
			player.body.hairType = Player::Body::HairType::hair5;
			break;
		case Player::Body::HairType::hair5:
			player.body.hairType = Player::Body::HairType::hair6;
			break;
		case Player::Body::HairType::hair6:
			player.body.hairType = Player::Body::HairType::hair7;
			break;
		case Player::Body::HairType::hair7:
			player.body.hairType = Player::Body::HairType::hair8;
			break;
		case Player::Body::HairType::hair8:
			player.body.hairType = Player::Body::HairType::hair1;
		}
	}
	else
		switch (player.body.hairType)
		{
		case Player::Body::HairType::hair8:
			player.body.hairType = Player::Body::HairType::hair7;
			break;
		case Player::Body::HairType::hair7:
			player.body.hairType = Player::Body::HairType::hair6;
			break;
		case Player::Body::HairType::hair6:
			player.body.hairType = Player::Body::HairType::hair5;
			break;
		case Player::Body::HairType::hair5:
			player.body.hairType = Player::Body::HairType::hair4;
			break;
		case Player::Body::HairType::hair4:
			player.body.hairType = Player::Body::HairType::hair3;
			break;
		case Player::Body::HairType::hair3:
			player.body.hairType = Player::Body::HairType::hair2;
			break;
		case Player::Body::HairType::hair2:
			player.body.hairType = Player::Body::HairType::hair1;
			break;
		case Player::Body::HairType::hair1:
			player.body.hairType = Player::Body::HairType::hair8;

		}
}


void Menu::changeBottomType(Player& player, bool increment)
{
	if (increment)
	{
		if (player.CharacterClothes.leg == Player::Clothing::noBottoms)
			player.CharacterClothes.leg = Player::Clothing::femaleBottom1;
		else if (player.CharacterClothes.leg == Player::Clothing::femaleBottom1)
			player.CharacterClothes.leg = Player::Clothing::femaleBottom2;
		else if (player.CharacterClothes.leg == Player::Clothing::femaleBottom2)
			player.CharacterClothes.leg = Player::Clothing::noBottoms;
	}
	else
	{
		if (player.CharacterClothes.leg == Player::Clothing::noBottoms)
			player.CharacterClothes.leg = Player::Clothing::femaleBottom2;
		else if (player.CharacterClothes.leg == Player::Clothing::femaleBottom2)
			player.CharacterClothes.leg = Player::Clothing::femaleBottom1;
		else if (player.CharacterClothes.leg == Player::Clothing::femaleBottom1)
			player.CharacterClothes.leg = Player::Clothing::noBottoms;
	}
}

void Menu::changeTopType(Player& player, bool increment)
{
	if (increment)
	{
		if (player.CharacterClothes.body == Player::Clothing::noTop)
			player.CharacterClothes.body = Player::Clothing::femaleTop1;
		else if (player.CharacterClothes.body == Player::Clothing::femaleTop1)
			player.CharacterClothes.body = Player::Clothing::femaleTop2;
		else if (player.CharacterClothes.body == Player::Clothing::femaleTop2)
			player.CharacterClothes.body = Player::Clothing::noTop;
	}
	else
	{
		if (player.CharacterClothes.body == Player::Clothing::noTop)
			player.CharacterClothes.body = Player::Clothing::femaleTop2;
		else if (player.CharacterClothes.body == Player::Clothing::femaleTop2)
			player.CharacterClothes.body = Player::Clothing::femaleTop1;
		else if (player.CharacterClothes.body == Player::Clothing::femaleTop1)
			player.CharacterClothes.body = Player::Clothing::noTop;
	}
}