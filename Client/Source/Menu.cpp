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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();


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

		}



		// END Rendering
		ImGui::Render();
		SDL_GL_MakeCurrent(window, glContext);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

/*
void Menu::CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, GL_Renderer& renderer, World& level)
{
	Button back("Back");
	Button singlePlayer("Start");
	Button loadSave("Load Save");
	Button rotatePlayer("Rotate");
	// LEFT SIDE (ORGANIC)
	// Gender
	// Skin colour
	// Eye Type
	// Eye Colour

	// Gender
	Button femaleGender("", "FemaleButton");
	Button maleGender("", "MaleButton");
	//Skin Colour
	Button ChangeSkinColourL("", "LButton");
	Button ChangeSkinColourR("", "RButton");
	//Hair
	Button ChangeHairTypeL("", "L_Button");
	Button ChangeHairTypeR("", "R_Button");
	//Eye
	Button ChangeEyeTypeL("", "L_Button");
	Button ChangeEyeTypeR("", "R_Button");
	//Ear
	Button ChangeEarTypeL("", "L_Button");
	Button ChangeEarTypeR("", "R_Button");
	// Colours
	Button ChangeBodyColour("Body Colour");
	Button ChangeEyeColour("Eye Colour");
	Button ChangeHairColour("Hair Colour");

	// Right Side ( CLOTHES)

	//Top
	Button changeTopL("", "L_Button");
	Button changeTopR("", "R_Button");
	// Bottom
	Button changeBottomL("", "L_Button");
	Button changeBottomR("", "R_Button");
	//Colour
	Button ChangeTopColour("Top Colour");
	Button ChangeBottomColour("Bottom Colour");



	Button randomiseAll("Random");

	Player playerCreation = gameSettings.getPlayerFromSave();

	// Load player from file
	playerCreation = gameSettings.getPlayerFromSave();
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5, gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	playerCreation.PlayerClothes.body = Player::Clothing::femaleTop1;
	playerCreation.PlayerClothes.leg = Player::Clothing::femaleBottom2;


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
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);

		/////// Organic customisation buttons //////

		int buttonSize = 50;
		int bSize2 = buttonSize * 2;
		int ObuttonsX = playerCreation.getX() - playerCreation.getSize().x;
		int ObuttonsY = playerCreation.getY() - buttonSize * 4;
		int CbuttonsX = playerCreation.getX() + playerCreation.getSize().x + bSize2;
		int CbuttonsY = playerCreation.getY() - buttonSize * 4;

		//femaleGender.getButtonBackgroundTexture().alterTextureColour(200, 150, 20);
		maleGender.render(renderer, ObuttonsX, ObuttonsY, buttonSize, buttonSize);
		femaleGender.render(renderer, ObuttonsX - bSize2, ObuttonsY, buttonSize, buttonSize);

		ChangeHairTypeL.render(renderer, ObuttonsX - bSize2, ObuttonsY + buttonSize * 2, buttonSize, buttonSize);
		ChangeHairTypeR.render(renderer, ObuttonsX, ObuttonsY + buttonSize * 2, buttonSize, buttonSize);

		ChangeEyeTypeL.render(renderer, ObuttonsX - bSize2, ObuttonsY + buttonSize * 3, buttonSize, buttonSize);
		ChangeEyeTypeR.render(renderer, ObuttonsX, ObuttonsY + buttonSize * 3, buttonSize, buttonSize);

		ChangeEarTypeL.render(renderer, ObuttonsX - bSize2, ObuttonsY + buttonSize * 4, buttonSize, buttonSize);
		ChangeEarTypeR.render(renderer, ObuttonsX, ObuttonsY + buttonSize * 4, buttonSize, buttonSize);

		ChangeBodyColour.render(renderer, ObuttonsX - buttonSize, ObuttonsY + buttonSize * 5, 200, 50);
		ChangeEyeColour.render(renderer, ObuttonsX - buttonSize, ObuttonsY + buttonSize * 6, 200, 50);
		ChangeHairColour.render(renderer, ObuttonsX - buttonSize, ObuttonsY + buttonSize * 7, 200, 50);


		// Clothes Customisation buttons ( RIGHT SIDE)
		changeTopL.render(renderer, CbuttonsX - bSize2, CbuttonsY + buttonSize * 2, buttonSize, buttonSize);
		changeTopR.render(renderer, CbuttonsX, CbuttonsY + buttonSize * 2, buttonSize, buttonSize);

		changeBottomL.render(renderer, CbuttonsX - bSize2, CbuttonsY + buttonSize * 3, buttonSize, buttonSize);
		changeBottomR.render(renderer, CbuttonsX, CbuttonsY + buttonSize * 3, buttonSize, buttonSize);

		ChangeTopColour.render(renderer, CbuttonsX - buttonSize, ObuttonsY + buttonSize * 5, buttonSize * 4, buttonSize);
		ChangeBottomColour.render(renderer, CbuttonsX - buttonSize, ObuttonsY + buttonSize * 6, buttonSize * 4, buttonSize);

		//changeBottom.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() + 100, 100, 50);


		randomiseAll.render(renderer, playerCreation.getX(), gameSettings.WINDOW_HEIGHT - buttonSize, buttonSize * 3, buttonSize);



		// BUTTON FUNCTIONALITY
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
		back.render(renderer, 50, 150, 100, 50);
		if (back.isPressed())
		{
			displayCharacterMenu = false;
			return;
		}

		// Start
		singleplayer.render(renderer, gameSettings.WINDOW_WIDTH / 2 + 200, gameSettings.WINDOW_HEIGHT - 100, buttonSize * 2, buttonSize);
		if (singleplayer.isPressed())
		{
			gameSettings.running = true;
			gameSettings.useNetworking = false;
			displayCharacterMenu = false;
			displayMainMenu = false;
		}

		loadSave.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT - 100 - buttonSize * 2, buttonSize * 2, buttonSize);
		if (loadSave.isPressed())
		{
			displayCharacterMenu = false;
			gameSettings.loadGameFromSave(level);
			player = gameSettings.getPlayerFromSave();
			displayMainMenu = false;
		}

		rotateplayer.render(renderer, gameSettings.WINDOW_WIDTH / 2, playerCreation.getY() + playerCreation.getSize().x / 2 + buttonSize, buttonSize * 2, buttonSize);
		if (rotateplayer.isPressed())
		{
			int rotation = playerCreation.getTargetRotation() + 90;
			if (rotation > 360)
				rotation = 0;
			playerCreation.setTargetRotation(rotation);
		}




		//Render the mouse cursor last
		if (renderCursor)
			cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	


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



















	/*
	void Menu::changeEarType(Player & player, bool increment)

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



	oid Menu::changeEyeType(Player & player, bool increment)

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



	oid Menu::changeHairType(Player & player, bool increment)

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



	oid Menu::changeBottomType(Player & player, bool increment)

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

	oid Menu::changeTopType(Player & player, bool increment)

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
		*/
	
