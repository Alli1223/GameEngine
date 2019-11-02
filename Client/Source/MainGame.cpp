#include "stdafx.h"
#include "MainGame.h"
#include "InitialisationError.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")



void showErrorMessage(const char* message, const char* title)
{
	// Note: this is specific to Windows, and would need redefining to work on Mac or Linux
	MessageBoxA(nullptr, message, title, MB_OK | MB_ICONERROR);
}
bool SetOpenGLAttributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

MainGame::MainGame()
{
	// Try and Connect to server
	try {
		int initNetwork = networkManager.init(world.I_player.playerName);
		if (initNetwork != 0)
			std::cout << "Error init network" << std::endl;
		gameSettings.useNetworking = true;
		std::cout << "Connected to server at IP: " << networkManager.getServerIP() << std::endl;
	}
	// Else single player
	catch (std::exception e)
	{
		gameSettings.useNetworking = false;
		std::cout << "Could not connect to server: " << e.what() << std::endl;
	}
	// Initialize video and otehr good SDL stuff
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError()) << std::endl;
		throw InitialisationError("SDL_Init failed");
	}	
	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	SDL_ShowCursor(SDL_DISABLE);

	// Set Window Size
	gameSettings.getScreenResolution();

	gameSettings.WINDOW_HEIGHT;
	gameSettings.WINDOW_WIDTH;
	if (!gameSettings.fullscreen)
	{
		gameSettings.WINDOW_WIDTH = 1920;  ///= 2 ;
		gameSettings.WINDOW_HEIGHT = 1080; // /= 2;
	}
	gameSettings.deltaTime = SDL_GetTicks();
	

	// Create the window
	if (gameSettings.fullscreen)
		window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	else
		window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Set attributed and create openGL context
	SetOpenGLAttributes();
	glContext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(0);	// V-sync 1 on, 0 off
	if (window == nullptr)
		throw InitialisationError("SDL_CreateWindow failed");

	// IF TTF Init error
	if (!TTF_WasInit() && TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}

	
	//init GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Initialisation Failed", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 410");

	ImGui::StyleColorsLight();
	// for different lighting
	//glEnable(GL_FRAMEBUFFER_SRGB);
}

MainGame::~MainGame()
{
	// clean up imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	SDL_GL_DeleteContext(glContext); // OpenGL
	//SDL_DestroyRenderer(renderer); // SDL
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MainGame::run()
{
	// Create renderer
	GL_Renderer glRenderer;

	//Menu menu;
	//menu.MainMenu(gameSettings, world, glRenderer.camera, world.I_player, glRenderer);

	// Initilise the world with the physcis stored in glRenderer
	world.InitiliseWorld(glRenderer);

	// Create text characters from ttf files
	glRenderer.CreateTextCharacterAtals();
	glRenderer.camera.windowSize.x = gameSettings.WINDOW_WIDTH;
	glRenderer.camera.windowSize.y = gameSettings.WINDOW_HEIGHT;
	glRenderer.camera.SetPos(0, 0);

	// Get ticks used for delta time
	int lastTicks = SDL_GetTicks();
	int currentTicks = SDL_GetTicks();

	// Music
	gMusic = Mix_LoadMUS("Resources\\Sounds\\Music\\Fantasy_Game_Loop.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Create player
	gameSettings.levelSaving.LoadWorld(world, world.I_player);
	world.I_player.setPosition(100,0);
	world.I_player.setSize(100, 100);
	world.I_player.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Character\\Alli.png");
	world.I_player.setEyeColour({ rand() % 255, rand() % 255 , rand() % 255 });
	world.I_player.setHairColour({ rand() % 255, rand() % 255 , rand() % 255 });

	// Create Level


	world.InfiniWorld.CreateInfiniWorld(glRenderer, world.I_Physics.get());

	ProceduralTerrain pt;
	//pt.populateTerrain(level);

	// Projection matrix
	glRenderer.SetProjectionMatrix();


	//ShopDisplayShelf displayShelf;
	//for (int i = 0; i < 5; i++)
	//			world.I_player.inventory.add(displayShelf.getSharedPointer());
	//Fish fish;
	//Hoe hoe;
	//FishingRod rod;
	//BugNet net;
	//Scythe scythe;
	//SunflowerSeeds sunflowerSeeds;
	//WheatSeeds wheatSeeds;
	//LavenderSeeds lavenderSeeds;

	//ItemChest chest;
	//chest.setPosition(0, 100);
	//chest.setSize(100, 100);
	//chest.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Character\\Alli.png");
	
	//world.I_player.inventory.add(wheatSeeds.getSharedPointer());
	//for(int i =0;i < 10; i++)
	//	world.I_player.inventory.add(sunflowerSeeds.getSharedPointer());
	//world.I_player.inventory.add(lavenderSeeds.getSharedPointer());
	//world.I_player.inventory.add(fish.getSharedPointer());
	//world.I_player.inventory.add(hoe.getSharedPointer());
	//world.I_player.inventory.add(rod.getSharedPointer());
	//world.I_player.inventory.add(net.getSharedPointer());
	//world.I_player.inventory.add(scythe.getSharedPointer());
	
	//world.onEnter(world.I_player);
	Room room;

	room.onEnter(world.I_player);
	//Shop.onEnter(world.I_player);
	//Mix_PlayMusic(gMusic, -1);

	//for (int i = 0; i < 10; i++)
	//{
	//	Firefly firefly;
	//	firefly.setPosition(rand() % 1000, rand() % 1000);
	//	world.insects.push_back(firefly.getSharedPointer());
	//}
	/////////////////////////////////////////////// MAIN LOOP ///////////////////////////////////////
	while (gameSettings.running)
	{
		// Set up ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		// Set up level
		level.setCellsInWindowSize(gameSettings.WINDOW_WIDTH / level.getCellSize(), gameSettings.WINDOW_HEIGHT / level.getCellSize());
		SDL_GetMouseState(&mouseX, &mouseY);

		// Compute timings
		currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - lastTicks) / 1000.0f;

		// Clear screen
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Process networking
		if(gameSettings.useNetworking)
			networkManager.NetworkUpdate(world,world.networkPlayers, world.I_player);
		
		// User input
		input.HandleUserInput(glRenderer, GameSettings::currentInstance->I_player, gameSettings, UI);

		// Update physics
		GameSettings::currentInstance->Update();

		// Render Scene
		GameSettings::currentInstance->Render(glRenderer);

		// Render game
		glRenderer.RenderAllLayers();

		// Render UI
		UI.Render(glRenderer, world, GameSettings::currentInstance->I_player, gameSettings);

		for each (auto npc in GameSettings::currentInstance->npcs)
		{
			npc->Render(glRenderer);
		}
		
		// END Rendering
		ImGui::Render();
		SDL_GL_MakeCurrent(window, glContext);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		SDL_GL_SwapWindow(window);

		if (gameSettings.displayFPS)
			gameSettings.CalculateFramesPerSecond();

		gameSettings.deltaTime = gameSettings.elapsedTime - gameSettings.lastFrameTimeElapsed;
		gameSettings.lastFrameTimeElapsed = gameSettings.elapsedTime;
		// End of loop
	}


	SDL_GL_DeleteContext(glContext);

	///// END GAME LOOP //////

	if (gameSettings.useNetworking)
	{
		// Send quit message and close socket when game ends
		networkManager.sendTCPMessage("QUIT\n");
		networkManager.socket->close();
	}

	// Save player settings when the game ends the game loop
	if (gameSettings.saveLevelOnExit && !gameSettings.useNetworking)
		gameSettings.levelSaving.SaveWorld(world, world.I_player);
	if (gameSettings.savePlayerOnExit)
		//gameSettings.savePlayerSettings(player);
		if (gameSettings.restartGame)
			needsRestart = true;
}

//if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
//{
//	std::cout << "Spawning Projectile" << std::endl;
//	float delta_x = gameSettings.WINDOW_WIDTH / 2 - mouseX;
//	float delta_y = gameSettings.WINDOW_HEIGHT / 2 - mouseY;
//	Projectile proj(glRenderer, world.I_Physics.get(), world.I_player.getPosition() + 200.0f, b2Vec2(-delta_x / 10000.0f, -delta_y / 10000.0f));
//	float rotation = atan2(delta_y, delta_x);
//	proj.setRotation(rotation);
//	world.projectiles.push_back(proj);
//	//world.I_playerShop->Shopfloor->onEnter(world.I_player);
//}