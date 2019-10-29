#pragma once
#include "GUI.h"
#include "Icon.h"
#include "Item.h"
class Button : public GUI
{
public:
	Button();
	Button(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
	//! Constructor (takes in text for the button) Leave " "" "  for no text
	Button(std::string newText);
	Button(std::string newText, std::string backgroundType);
	//! Destructor
	~Button();
	//! Render the button
	void Render(GL_Renderer& renderer);

	//! Change the buttons text
	std::string setText(std::string newText) { return text = newText; }

	//! If the button should increase size when mouseover
	bool setMouseOverIncreaseSize(int yayOrNay) { return mouseOverIncreaseSize = yayOrNay; }
	int setSizeIncrease(int newSize) { return mouseOverSizeInrease = newSize; }

	//! If the button has been pressed
	bool isPressed();
	bool isHovered();
	void UpdateInfo();


	//! pointer to buttons item (if any)
	std::vector<std::shared_ptr<Item>> buttonItem;

private:
	//! Buttons text
	std::string text;
	double timeButtonWasPressed = 0.0;
	double buttonTimeout = 0.3;
	//! mouse position
	int tx, ty;
	//! if the button is active
	bool isActivated = false;
	bool timeout = false;
	bool isMouseOver = false;

	//! Text size
	float textSize = 0.2f;

	bool mouseOverIncreaseSize = true;
	int mouseOverSizeInrease = 5;
	//! buttons texture location
	std::string buttonTextureLocation = "Resources\\UI\\";

};

