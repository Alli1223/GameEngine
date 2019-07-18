#include "stdafx.h"
#include "UntitledGame.h"
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

UntitledGame::UntitledGame()
{
	// Try and Connect to server
	try {
		int initNetwork = networkManager.init(world.player.playerName);
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
		window = SDL_CreateWindow("Magic Cafe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	else
		window = SDL_CreateWindow("Magic Cafe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

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

UntitledGame::~UntitledGame()
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

void UntitledGame::run()
{
	// Create renderer
	GL_Renderer glRenderer;

	

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
	gameSettings.levelSaving.LoadWorld(world, world.player);
	world.player.setPosition(100,0);
	world.player.setSize(100, 100);
	//world.player.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Character\\Alli.png");
	world.player.setEyeColour({ rand() % 255, rand() % 255 , rand() % 255 });
	world.player.setHairColour({ rand() % 255, rand() % 255 , rand() % 255 });

	// Create Level


	//world.InfiniWorld.CreateInfiniWorld(glRenderer);


	ProceduralTerrain pt;
	//pt.populateTerrain(level);
	//level = gameSettings.loadGameFromSave("Resources\\Map\\Testing_Map.json");

	// Projection matrix
	glRenderer.SetProjectionMatrix();


	//ShopDisplayShelf displayShelf;
	//for (int i = 0; i < 5; i++)
	//			world.player.inventory.add(displayShelf.getSharedPointer());
	Fish fish;
	Hoe hoe;
	FishingRod rod;
	BugNet net;
	Scythe scythe;
	SunflowerSeeds sunflowerSeeds;
	WheatSeeds wheatSeeds;
	LavenderSeeds lavenderSeeds;

	ItemChest chest;
	chest.setPosition(0, 100);
	chest.setSize(100, 100);
	//chest.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\Character\\Alli.png");
	
	//world.player.inventory.add(wheatSeeds.getSharedPointer());
	//for(int i =0;i < 10; i++)
	//	world.player.inventory.add(sunflowerSeeds.getSharedPointer());
	//world.player.inventory.add(lavenderSeeds.getSharedPointer());
	//world.player.inventory.add(fish.getSharedPointer());
	//world.player.inventory.add(hoe.getSharedPointer());
	//world.player.inventory.add(rod.getSharedPointer());
	//world.player.inventory.add(net.getSharedPointer());
	//world.player.inventory.add(scythe.getSharedPointer());

	//Mix_PlayMusic(gMusic, -1);

	//for (int i = 0; i < 10; i++)
	//{
	//	Firefly firefly;
	//	firefly.setPosition(rand() % 1000, rand() % 1000);
	//	world.insects.push_back(firefly.getSharedPointer());
	//}

	// Initilise the world with the physcis stored in glRenderer
	world.InitiliseWorld(glRenderer);

	/////////////////////////////////////////////// MAIN LOOP ///////////////////////////////////////
	while (gameSettings.running)
	{
		// Set up ImGui
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplSDL2_NewFrame(window);
		//ImGui::NewFrame();


		// Set up level
		level.setCellsInWindowSize(gameSettings.WINDOW_WIDTH / level.getCellSize(), gameSettings.WINDOW_HEIGHT / level.getCellSize());
		SDL_GetMouseState(&mouseX, &mouseY);

		currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - lastTicks) / 1000.0f;
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(gameSettings.useNetworking)
			networkManager.NetworkUpdate(world, world.player);
		
		// User input
		//Player* tet = world.currentInstance->I_Player;
		if(world.currentInstance != nullptr)
			input.HandleUserInput(glRenderer, world.instances->I_Player, gameSettings, UI);

		// Set easy access variables
		glRenderer.camera.mouse_position = { (float)mouseX, (float)mouseY };
		glRenderer.playerPosition = world.player.getPosition();
		//world.player.cellPos = world.player.getPosition() / (float)world.InfiniWorld.getCellSize();
		gameSettings.mouseCellPos.x = mouseX / level.getCellSize() + glRenderer.camera.getX() / level.getCellSize() + 1;
		gameSettings.mouseCellPos.y = mouseY / level.getCellSize() + glRenderer.camera.getY() / level.getCellSize() + 1;

		// Camera to players position
		glm::vec2 halfCameraSize = { glRenderer.camera.windowSize.x / 2, glRenderer.camera.windowSize.y / 2 };
		glRenderer.camera.Lerp_To(world.player.getPosition() - halfCameraSize, glRenderer.camera.getCameraSpeed());



		// Day night cycle
		//glRenderer.timeOfDay = sin(SDL_GetTicks() / 100000.0f); // 100ms
		//if (glRenderer.timeOfDay <= 0.0)
		//	glRenderer.timeOfDay = 0.0;
		//if (glRenderer.timeOfDay >= 1.0)
		//	glRenderer.timeOfDay = 1.0;


		glRenderer.playerPosition = world.player.getPosition();

		//Update instance
		if (world.currentInstance != nullptr)
		{
			world.currentInstance->Update();

			//world.currentInstance->Render(glRenderer);
		}
		// Render game
		rendering.RenderObjects(world, glRenderer, world.player, gameSettings);
		glRenderer.RenderAllLayers();

		// Render UI
		//UI.Render(glRenderer, world, world.player, gameSettings);

		for (int i = 0; i < networkManager.allPlayers.size(); i++)
		{
			//networkManager.allPlayers[i]->Render(glRenderer);
		}

		//if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		//{
		//	float delta_x = gameSettings.WINDOW_WIDTH/2 - mouseX;
		//	float delta_y = gameSettings.WINDOW_HEIGHT/2 - mouseY;
		//	Projectile proj(glRenderer, glRenderer.p_World.get(),world.player.getPosition() + 200.0f, b2Vec2(-delta_x / 10000.0f, -delta_y / 10000.0f));
		//	float rotation = atan2(delta_y, delta_x);
		//	proj.setRotation(rotation);
		//	world.projectiles.push_back(proj);
		//}
		//std::cout << world.player.getX() << " " << world.player.getY() << std::endl;
		ivec2 posi;
		if (SDL_GetMouseState(&posi.x, &posi.y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			//world.GetCell((posi.x +glRenderer.camera.getX()) / 100.0f, (posi.y + glRenderer.camera.getY()) / 100.0f)->AssignType(2,"Sand");
			//std::vector<Point> path = pathfinder.findPath(world, { 2,1 }, { 10,3 });
		}
		//glRenderer.RenderLine(glRenderer.camera.mouse_position, { 0,0 });
		//glRenderer.RenderText("Hello World too this is a test bit of text", { 0.5,0.5 }, { 1.0,1.0 }, { 255,255,255 });









		// END Rendering
		ImGui::Render();
		SDL_GL_MakeCurrent(window, glContext);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
		gameSettings.levelSaving.SaveWorld(world, world.player);
	if (gameSettings.savePlayerOnExit)
		//gameSettings.savePlayerSettings(player);
		if (gameSettings.restartGame)
			needsRestart = true;
}