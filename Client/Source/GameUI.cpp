#include "stdafx.h"
#include "GameUI.h"


GameUI::GameUI()
{
	
}


GameUI::~GameUI()
{
}

void GameUI::Init(Player& player, GameSettings& gs)
{
	console.Init(gs);
	characterWindow.init(player);
}


void GameUI::Render(GL_Renderer& renderer, World& world, Player& player, GameSettings& gameSettings)
{
	characterWindow.Render(renderer);
	worldEdit.Render(renderer, world, player);

	if (player.isInBuilding)
	{
		roomDesigner.Render(renderer);
	}

	for each (auto npc in GameSettings::currentInstance->npcs)
	{
		npc->Render(renderer);
	}


	bool show_demo_window = true;

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Game Editor");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

		if (ImGui::Button("Exit", { 50,50 }))
			gameSettings.running = false;

		ImGui::SameLine();
		//if (ImGui::Button("Save Shop", { 100,50 }))
		//{
		//	gameSettings.levelSaving.SaveInstance(GameSettings::currentInstance);
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Load Shop", { 100,50 }))
		//{
		//	//GameSettings::currentInstance =  gameSettings.levelSaving.LoadInstance();
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Save Level", { 100,50 }))
		//{
		//	gameSettings.levelSaving.SaveLevel(world);
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Save Player", { 100,50 }))
		//{
		//	gameSettings.levelSaving.SavePlayer(player);
		//}
		ImGui::SliderFloat("Time of day", &renderer.timeOfDay, 0.0f, 1.0f, "%.3f", (1.0f));

		ImGui::Text("player position = %f, %f",player.getX(), player.getY());
		ImGui::Text("player position = %f, %f", player.getX() / 100.0f, player.getY() / 100.0f);

		ImGui::Text("mouse = %f, %f", renderer.camera.mouse_position.x, renderer.camera.mouse_position.y);

		ImGui::Text("Mouse Cell Pos = %f, %f", (renderer.camera.mouse_position.x + renderer.camera.getX()) / world.getCellSize(), (renderer.camera.mouse_position.y + renderer.camera.getY()) / world.getCellSize());
		ImGui::Text("Camera Position = %f, %f", renderer.camera.getPosition().x, renderer.camera.getY());

		ImGui::Text("Total Lights: %d", renderer.lights.size());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}



	toolbar.Render(renderer, world, player, gameSettings);
	console.Render(renderer);
}