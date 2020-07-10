#pragma once
#include "player.h"
#include "Texture.h"
#include "Camera.h"
#include "Button.h"
#include "GameSettings.h"
#include "ColourSlider.h"
#include "TextInput.h"
#include "NetworkManager.h"
class Menu
{
public:
	//! Constructor
	Menu();
	//! Destroctor
	~Menu();

	//! Character List
	void CharacterSelection(GameSettings& gameSettings, GL_Renderer& renderer, World& level, Player& player);

	//! Run main menu loop
	void MainMenu(GameSettings& gameSettings, World& level, Camera& camera, Player& player, GL_Renderer& renderer, SDL_Window* window, SDL_GLContext& glContext, NetworkManager& nm);

	//! Run character screen loop
	void CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, GL_Renderer& renderer, World& level);

	// Set mouse pointer size
	int setCursorSize(int newCursorSize) { return menuCursorSize = newCursorSize; }

	std::vector<Player> existingPlayers;


private:
	//! Change body buttons
	void changeEarType(Player& player, bool increment);
	void changeEyeType(Player& player, bool increment);
	void changeHairType(Player& player, bool increment);
	void changeTopType(Player& player, bool increment);
	void changeBottomType(Player& player, bool increment);
	//! To end main menu while loop
	bool displayMainMenu = true;
	//! To end character menu while loop
	bool displayCharacterMenu = true;
	//! To end selection menu while loop
	bool displaySlectionMenu = true;
	//! Texture locations
	std::string menuTextures = "Resources\\UI\\";
	std::string otherTextures = "Resources\\Sprites\\Menu\\";

	//! mouse pos and initial cursor size
	int mouseX, mouseY;
	int menuCursorSize = 30;
	bool showColourSlider = false;
	bool renderCursor = true;

	SDL_Window* window;
	SDL_GLContext* glContext;

	ColourSlider bodyColourSlider;
	ColourSlider eyeColourSlider;
	ColourSlider hairColourSlider;
	ColourSlider topColourSlider;
	ColourSlider bottomColourSlider;
};

