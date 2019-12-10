#pragma once
#include "player.h"
#include "Texture.h"
#include "Camera.h"
#include "Button.h"
#include "GameSettings.h"
#include "ColourSlider.h"
class Menu
{
public:
	//! Constructor
	Menu();
	//! Destroctor
	~Menu();

	//! Run main menu loop
	void MainMenu(GameSettings& gameSettings, World& level, Camera& camera, Player& player, GL_Renderer& renderer, SDL_Window* window, SDL_GLContext& glContext);

	//! Run character screen loop
	void CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, GL_Renderer& renderer, World& level);

	// Set mouse pointer size
	int setCursorSize(int newCursorSize) { return menuCursorSize = newCursorSize; }



private:
	//! Change body buttons
	//void changeEarType(Player& player, bool increment);
	//void changeEyeType(Player& player, bool increment);
	//void changeHairType(Player& player, bool increment);
	//void changeTopType(Player& player, bool increment);
	//void changeBottomType(Player& player, bool increment);
	//! To end main menu while loop
	bool displayMainMenu = true;
	//! To end character menu while loop
	bool displayCharacterMenu = true;
	//! Texture locations
	std::string menuTextures = "Resources\\UI\\";
	std::string otherTextures = "Resources\\Sprites\\Menu\\";

	//! mouse pos and initial cursor size
	int mouseX, mouseY;
	int menuCursorSize = 30;
	bool showColourSlider = false;
	bool renderCursor = true;

	//ColourSlider bodyColourSlider;
	//ColourSlider eyeColourSlider;
	//ColourSlider hairColourSlider;
	//ColourSlider topColourSlider;
	//ColourSlider bottomColourSlider;
};

