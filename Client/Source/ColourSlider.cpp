#include "stdafx.h"
#include "ColourSlider.h"


ColourSlider::ColourSlider() :IncrementHue("", "R_Button"), DecrementHue("", "L_Button"), IncrementSaturation("", "R_Button"), DecrementSaturation("", "L_Button"), IncrementLuminance("", "R_Button"), DecrementLuminance("", "L_Button")
{
}


ColourSlider::~ColourSlider()
{
}

void ColourSlider::Setup() 
{
	setup = false;
	HueSlider = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\HueSlider.png");
	LuminanceSlider = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\LuminanceSlider.png");
	SaturationSlider = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\SaturationSlider.png");
	sliderIcon = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\SliderIndicator.png");

	// HUE
	IncrementHue.setPosition(getX() + getWidth() / 2 + buttonSize, getY() - 50);
	IncrementHue.setSize(buttonSize, buttonSize);
	IncrementHue.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\R_Button.png");

	DecrementHue.setPosition(getX() - getWidth() / 2 - buttonSize, getY() - 50);
	DecrementHue.setSize(buttonSize, buttonSize);
	DecrementHue.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\L_Button.png");

	// Saturation
	IncrementSaturation.setPosition({ getX() + getWidth() / 3.6 / 2 + buttonSize, getY() });
	IncrementSaturation.setSize(buttonSize, buttonSize);
	IncrementSaturation.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\R_Button.png");

	DecrementSaturation.setPosition({ getX() - getWidth() / 3.6 / 2 - buttonSize, getY() });
	DecrementSaturation.setSize(buttonSize, buttonSize);
	DecrementSaturation.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\L_Button.png");

	// Luminance
	IncrementLuminance.setPosition({ getX() + getWidth() / 3.6 / 2 + buttonSize, getY() + 50 });
	IncrementLuminance.setSize(buttonSize, buttonSize);
	IncrementLuminance.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\R_Button.png");

	DecrementLuminance.setPosition({ getX() - getWidth() / 3.6 / 2 - buttonSize, getY() + 50 });
	DecrementLuminance.setSize(buttonSize, buttonSize);
	DecrementLuminance.Background = ResourceManager::LoadTexture("Resources\\UI\\Buttons\\L_Button.png");



}


void ColourSlider::Render(GL_Renderer& renderer)
{
	if(setup)
		Setup();
	bool useOffset = false;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (x > getX() - getWidth() / 2 && x < getX() + getWidth() / 2 && y > getY() - 75 && y < getY() - 25)
		{
			hueValue = x - getX() + getWidth() / 2;
		}
		if (x > getX() - getWidth() / 3.6 / 2 && x < getX() + getWidth() / 2 / 3.6 && y > getY() - 25 && y < getY() + 25)
		{
			saturationValue = x - getX() + getWidth() / 2 / 3.6;
		}
		if (x > getX() - getWidth() / 3.6 / 2 && x < getX() + getWidth() / 2 / 3.6 && y > getY() + 25 && y < getY() + 75)
		{
			LuminanceValue = x - getX() + getWidth() / 2 / 3.6;
		}
	}

	// Buttons

	DecrementHue.Render(renderer);
	IncrementHue.Render(renderer);

	DecrementSaturation.Render(renderer);
	IncrementSaturation.Render(renderer);

	DecrementLuminance.Render(renderer);
	IncrementLuminance.Render(renderer);

	// Sliders

	glm::vec2 hueposition = { getX(), getY() - 50 };
	glm::vec2 huesize = { getWidth(), getHeight() / 3 };
	renderer.RenderGUI(HueSlider, hueposition, huesize, 0.0f, 0.5f, colour, flipSprite);

	glm::vec2 saturationposition = { getX(), getY() - 50 };
	glm::vec2 saturationsize = { getWidth(), getHeight() / 3 };
	renderer.RenderGUI(SaturationSlider, saturationposition, saturationsize, 0.0f, 0.5f, colour, flipSprite);

	glm::vec2 ssliderIconposition = { getX() - 50 + saturationValue, getY() };
	glm::vec2 ssliderIconsize = { sliderWidth, getHeight() / 3 };
	renderer.RenderGUI(sliderIcon, ssliderIconposition, ssliderIconsize, 0.0f, 0.5f, colour, flipSprite);
	//if(!useOffset)
	//	sliderIcon.render(renderer, getX() + hueValue - 180, getY() - 50, sliderWidth, getHeight() / 3);
	//else
	//	sliderIcon.render(renderer, getX() + hueValue, getY() - 50, sliderWidth, getHeight() / 3);


	renderer.RenderGUI(HueSlider, hueposition, huesize, 0.0f, 0.5f, colour, flipSprite);

	// Luminance
	glm::vec2 lsliderIconposition = { getX() - 50 + LuminanceValue, getY() + 50 };
	glm::vec2 lsliderIconsize = { sliderWidth, getHeight() / 3 };
	renderer.RenderGUI(sliderIcon, ssliderIconposition, lsliderIconsize, 0.0f, 0.5f, colour, flipSprite);
	//LuminanceSlider.alterTextureColour(colour);
	//LuminanceSlider.render(renderer, getX(), getY() + 50, getWidth() / 3.6, getHeight() / 3);
	//sliderIcon.render(renderer, getX() - 50 + LuminanceValue, getY() + 50, sliderWidth, getHeight() / 3);

	
	// Hue Buttons
	if (DecrementHue.isPressed())
		if(hueValue - incrementSpeed >= 0 && hueValue <= 360)
			hueValue -= incrementSpeed;
	if (IncrementHue.isPressed())
		if (hueValue >= 0 && hueValue + incrementSpeed <= 360)
			hueValue += incrementSpeed;

	// Saturation Buttons
	if (DecrementSaturation.isPressed())
		if (saturationValue - incrementSpeed >= 0 && saturationValue <= 100)
			saturationValue -= incrementSpeed;
	if (IncrementSaturation.isPressed())
		if (saturationValue >= 0 && saturationValue + incrementSpeed <= 100)
			saturationValue += incrementSpeed;

	// Luminance Buttons
	if (DecrementLuminance.isPressed())
		if (LuminanceValue - incrementSpeed >= 0 && LuminanceValue <= 100)
			LuminanceValue -= incrementSpeed;
	if (IncrementLuminance.isPressed())
		if (LuminanceValue >= 0 && LuminanceValue + incrementSpeed <= 100)
			LuminanceValue += incrementSpeed;

	hsl.Hue = hueValue;
	hsl.Saturation = saturationValue;
	hsl.Luminance = LuminanceValue;

	colour = hsl.TurnToRGB();
	
}




