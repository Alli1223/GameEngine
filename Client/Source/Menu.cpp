#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{

}

Menu::~Menu()
{
}

//Uint32 get_pixel_at(Uint32 * pixels, int x, int y, int w)
//{
//	return pixels[y * w + x];
//}
//
//std::shared_ptr<Button> get_instance(Button& n)
//{
//	return std::make_shared<Button>(n);
//}


void Menu::MainMenu(GameSettings& gameSettings, World& level, Camera& camera, Player& player, GL_Renderer& renderer, SDL_Window* window, SDL_GLContext& glContext)
{
	this->window = window;
	this->glContext = &glContext;
	// Create buttons
	//Button characterScreen("Character Customisation");
	//Button exit({ 50,25 }, { 100,50 }, ResourceManager::LoadTexture("Resources\\UI\\Background.png"), { 255,255,255 });
	Button exit("Exit");
	exit.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\Plain_Button.png");
	exit.setPosition({ camera.windowSize.x / 2, camera.windowSize.y / 2 - 80 });
	exit.setSize({ 200,40 });
	exit.setColour({ 200,100,50 });
	exit.textColour = { 255,255,255 };

	Button play("Play");
	play.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\Plain_Button.png");
	play.setPosition({ camera.windowSize.x / 2, camera.windowSize.y / 2 + 80 });
	play.setSize({ 200,40 });
	play.setColour({ 200,100,50 });
	play.textColour = { 255,255,255 };
	//exit.transparency = 0.5f;

	//Button play("Play");
	//play.Background = ResourceManager::LoadTexture("Resources\\UI\\Background.png");
	//
	//Button useNetworking("Multiplayer");
	//Button Fullscreen("FullScreen");
	//Button loadFromSave("Load Save Game");
	//Button play("New Game");


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
		//SDL_ShowCursor(SDL_DISABLE);
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//SDL_RenderClear(renderer);
		//menuBackground.alterTransparency(100);
		//menuBackground.alterTextureColour(150, 150, 150);
		//menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);


		int menuY = gameSettings.WINDOW_HEIGHT / 2;
		int menuX = gameSettings.WINDOW_WIDTH / 2;
		int menuSeperationDistance = 75;
		int buttonHeight = 50;
		int buttonWidth = 200;



		// Render buttons
		exit.Render(renderer);
		play.Render(renderer);

		if (play.isPressed())
		{
			CharacterCustomisationMenu(gameSettings, camera, player, renderer, level);
		}

		if (exit.isPressed())
		{
			gameSettings.running = false;
			break;
		}



		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		SDL_GL_SwapWindow(window);











		/*
		// New Game
		play.Render(renderer, menuX, menuY - menuSeperationDistance * 2, buttonWidth, buttonHeight);
		if (play.isPressed())
		{
			displayCharacterMenu = true;
			CharacterCustomisationMenu(gameSettings, camera, player, renderer, level);
			//displayMainMenu = false;
		}

		loadFromSave.render(renderer, menuX, menuY - menuSeperationDistance, buttonWidth, buttonHeight);

		// Load from save
		if (loadFromSave.isPressed())
		{
			gameSettings.loadGameFromSave("test");
			player = gameSettings.getPlayerFromSave();
			displayMainMenu = false;
		}

		// Dont save data when exit is pressed
		if (exit.isPressed())
		{
			gameSettings.running = false;
			gameSettings.saveLevelOnExit = false;
			gameSettings.savePlayerOnExit = false;
			displayMainMenu = false;
		}
		// Character Screen
		characterScreen.render(renderer);
		if (characterScreen.isPressed())
		{
			CharacterCustomisationMenu(gameSettings, camera, player, renderer, level);
			displayCharacterMenu = true;
		}

		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}

	*/
	}
}


void Menu::CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, GL_Renderer& renderer, World& level)
{


	Player playerCreation = gameSettings.getPlayerFromSave();

	// Load player from file
	playerCreation = gameSettings.getPlayerFromSave();
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5, gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	playerCreation.PlayerClothes.body = Player::Clothing::femaleTop1;
	playerCreation.PlayerClothes.leg = Player::Clothing::femaleBottom2;
	playerCreation.setRenderLayer(0);

	/////// Organic customisation buttons //////

	int buttonSize = 50;
	int bSize2 = buttonSize * 2;
	int ObuttonsX = playerCreation.getX() - playerCreation.getSize().x;
	int ObuttonsY = playerCreation.getY() - buttonSize * 4;
	int CbuttonsX = playerCreation.getX() + playerCreation.getSize().x + bSize2;
	int CbuttonsY = playerCreation.getY() - buttonSize * 4;

	// Create buttons
	Button back("", { 100,100 }, "Resources\\UI\\Buttons\\NoButton.png", { 100,100 }, { 200,100,50 }, { 255,255,255 });
	Button confirm("", { camera.windowSize.x - 200, camera.windowSize.y / 2 + 400 }, "Resources\\UI\\Buttons\\Confirm.png", { 200,50 }, { 200,100,50 }, { 255,255,255 });
	Button loadSave("Load Save", { camera.windowSize.x / 2, camera.windowSize.y / 2 + (camera.windowSize.y / 4) }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, { 200,100,50 }, { 255,255,255 });


	// LEFT SIDE (ORGANIC)
	// Gender
	// Skin colour
	// Eye Type
	// Eye Colour
	int leftPosition1 = camera.windowSize.x / 2 - camera.windowSize.x / 4;
	int leftPosition2 = camera.windowSize.x / 2 - camera.windowSize.x / 4 - 100;
	glm::vec3 buttonColour = {200,150,150};

	// Genders
	Button femaleGender("", { playerCreation.getX() - leftPosition1, playerCreation.getY() - 100 }, "Resources\\UI\\Buttons\\FemaleButton.png", { 50,50 }, buttonColour, { 255,255,255 });
	Button maleGender("", { playerCreation.getX() - leftPosition2, playerCreation.getY() - 100 }, "Resources\\UI\\Buttons\\MaleButton.png", { 50,50 }, buttonColour, { 255,255,255 });
	// Colours
	//Skin Colour
	//Button ChangeSkinColourL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Button ChangeSkinColourR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	////Hair Colour
	//Button ChangeHairColourL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Button ChangeHairColourR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	////Eye Colour
	//Button ChangeEyeColourL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() + 100 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Button ChangeEyeColourR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() + 100 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });

	//Types
	//Hair Type
	Button ChangeHairTypeL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	Button ChangeHairTypeR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Ear
	Button ChangeEarTypeL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	Button ChangeEarTypeR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Eye
	Button ChangeEyeTypeL("", { playerCreation.getX() - leftPosition1, playerCreation.getY() + 100 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	Button ChangeEyeTypeR("", { playerCreation.getX() - leftPosition2, playerCreation.getY() + 100 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });


	// Colours
	Button ChangeBodyColour("Body Colour", { playerCreation.getX() - leftPosition1 + 50, playerCreation.getY() + 200 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, { 255,255,255 });
	Button ChangeEyeColour("Eye Colour", { playerCreation.getX() - leftPosition1 + 50, playerCreation.getY()  + 250}, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, { 255,255,255 });
	Button ChangeHairColour("Hair Colour", { playerCreation.getX() - leftPosition1 + 50, playerCreation.getY() + 300 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, { 255,255,255 });


	// Right Side ( CLOTHES)
	int rightPosition1 = camera.windowSize.x / 2 - camera.windowSize.x / 4 - 100;
	int rightPosition2 = camera.windowSize.x / 2 - camera.windowSize.x / 4;
	int rightPositionCenter = camera.windowSize.x / 2 - camera.windowSize.x / 4 - 50;

	//Top
	Button changeTopL("", { playerCreation.getX() + rightPosition1, playerCreation.getY() }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	Button changeTopR("", { playerCreation.getX() + rightPosition2, playerCreation.getY() }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Bottom
	Button changeBottomL("", { playerCreation.getX() + rightPosition1, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\L_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	Button changeBottomR("", { playerCreation.getX() + rightPosition2, playerCreation.getY() + 50 }, "Resources\\UI\\Buttons\\R_Button.png", { 50,50 }, buttonColour, { 255,255,255 });
	//Colour
	Button ChangeTopColour("Top Colour", { playerCreation.getX() + rightPositionCenter, playerCreation.getY() + 200 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, { 255,255,255 });
	Button ChangeBottomColour("Bottom Colour", { playerCreation.getX() + rightPositionCenter, playerCreation.getY() + 250 }, "Resources\\UI\\Buttons\\Plain_Button.png", { 200,50 }, buttonColour, { 255,255,255 });



	Button randomiseAll("Random");




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

		playerCreation.Render(renderer);

		changeTopL.Render(renderer);
		changeTopR.Render(renderer);

		changeBottomL.Render(renderer);
		changeBottomR.Render(renderer);

		ChangeTopColour.Render(renderer);
		ChangeBottomColour.Render(renderer);


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
			gameSettings.useNetworking = false;
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
		player.PlayerClothes = playerCreation.PlayerClothes;
		player.setHairColour(playerCreation.gethairColour().r, playerCreation.gethairColour().g, playerCreation.gethairColour().b);
		player.setEyeColour(playerCreation.getEyeColour().r, playerCreation.getEyeColour().g, playerCreation.getEyeColour().b);
		player.setJacketColour(playerCreation.getJacketColour().r, playerCreation.getJacketColour().g, playerCreation.getJacketColour().b);
		player.setJeansColour(playerCreation.getJeansColour().r, playerCreation.getJeansColour().g, playerCreation.getJeansColour().b);
		player.body = playerCreation.body;
		player.setBodyColour(playerCreation.getBodyColour().r, playerCreation.getBodyColour().g, playerCreation.getBodyColour().b);

	}

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
		if (player.PlayerClothes.leg == Player::Clothing::noBottoms)
			player.PlayerClothes.leg = Player::Clothing::femaleBottom1;
		else if (player.PlayerClothes.leg == Player::Clothing::femaleBottom1)
			player.PlayerClothes.leg = Player::Clothing::femaleBottom2;
		else if (player.PlayerClothes.leg == Player::Clothing::femaleBottom2)
			player.PlayerClothes.leg = Player::Clothing::noBottoms;
	}
	else
	{
		if (player.PlayerClothes.leg == Player::Clothing::noBottoms)
			player.PlayerClothes.leg = Player::Clothing::femaleBottom2;
		else if (player.PlayerClothes.leg == Player::Clothing::femaleBottom2)
			player.PlayerClothes.leg = Player::Clothing::femaleBottom1;
		else if (player.PlayerClothes.leg == Player::Clothing::femaleBottom1)
			player.PlayerClothes.leg = Player::Clothing::noBottoms;
	}
}

void Menu::changeTopType(Player& player, bool increment)
{
	if (increment)
	{
		if (player.PlayerClothes.body == Player::Clothing::noTop)
			player.PlayerClothes.body = Player::Clothing::femaleTop1;
		else if (player.PlayerClothes.body == Player::Clothing::femaleTop1)
			player.PlayerClothes.body = Player::Clothing::femaleTop2;
		else if (player.PlayerClothes.body == Player::Clothing::femaleTop2)
			player.PlayerClothes.body = Player::Clothing::noTop;
	}
	else
	{
		if (player.PlayerClothes.body == Player::Clothing::noTop)
			player.PlayerClothes.body = Player::Clothing::femaleTop2;
		else if (player.PlayerClothes.body == Player::Clothing::femaleTop2)
			player.PlayerClothes.body = Player::Clothing::femaleTop1;
		else if (player.PlayerClothes.body == Player::Clothing::femaleTop1)
			player.PlayerClothes.body = Player::Clothing::noTop;
	}
}