#include "stdafx.h"
#include "ColourSlider.h"


ColourSlider::ColourSlider() :IncrementHue("", "R_Button"), DecrementHue("", "L_Button"), IncrementSaturation("", "R_Button"), DecrementSaturation("", "L_Button"), IncrementLuminance("", "R_Button"), DecrementLuminance("", "L_Button")
{
}


ColourSlider::~ColourSlider()
{
}


void ColourSlider::Render(SDL_Renderer* renderer)
{
	/*
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

	// HUE
	DecrementHue.render(renderer, getX() - getWidth() / 2 - buttonSize, getY() - 50, buttonSize, buttonSize);
	IncrementHue.render(renderer, getX() + getWidth() / 2 + buttonSize, getY() - 50, buttonSize, buttonSize);
	HueSlider.render(renderer, getX(), getY() - 50, getWidth(), getHeight() / 3);
	if(!useOffset)
		sliderIcon.render(renderer, getX() + hueValue - 180, getY() - 50, sliderWidth, getHeight() / 3);
	else
		sliderIcon.render(renderer, getX() + hueValue, getY() - 50, sliderWidth, getHeight() / 3);

	// Saturation
	DecrementSaturation.render(renderer, getX() - getWidth() / 3.6 / 2 - buttonSize, getY(), buttonSize, buttonSize);
	IncrementSaturation.render(renderer, getX() + getWidth() / 3.6 / 2 + buttonSize, getY(), buttonSize, buttonSize);
	SaturationSlider.alterTextureColour(colour);
	SaturationSlider.render(renderer, getX(), getY(), getWidth() / 3.6, getHeight() / 3);
	sliderIcon.render(renderer, getX() - 50 + saturationValue, getY(), sliderWidth, getHeight() / 3);

	// Luminance
	DecrementLuminance.render(renderer, getX() - getWidth() / 3.6 / 2 - buttonSize, getY() + 50, buttonSize, buttonSize);
	IncrementLuminance.render(renderer, getX() + getWidth() / 3.6 / 2 + buttonSize, getY() + 50, buttonSize, buttonSize);
	//LuminanceSlider.alterTextureColour(colour);
	LuminanceSlider.render(renderer, getX(), getY() + 50, getWidth() / 3.6, getHeight() / 3);
	sliderIcon.render(renderer, getX() - 50 + LuminanceValue, getY() + 50, sliderWidth, getHeight() / 3);

	
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
	*/
}




