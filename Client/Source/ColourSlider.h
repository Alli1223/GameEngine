#pragma once
#include "stdafx.h"
#include "GUI.h"
#include "HSL.h"
#include "Button.h"
//https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
class ColourSlider : public GUI
{
public:
	//! Constructor
	ColourSlider();
	//! Destructor
	~ColourSlider();

	void Setup();

	//! Render the colour slider
	void Render(GL_Renderer& renderer);

	//! Get and set default colours
	vec3 getColour() { return colour; }
	vec3 setColour(vec3 newColour) { return colour = newColour; }

	//! HSL (Hue, Saturation, Luminance)  for converting HSL from and to RGB
	HSL hsl;

	//! Set HSL Colour
	int setHSLColour(int H, int S, int L) { return hueValue = H, saturationValue = S, LuminanceValue = L; }

	bool isEnabled() { return enabled; }
	bool Disable() { return enabled = false; }
	bool Enable() { return enabled = true; }

private:
	//! Whether the slider is visiable
	bool enabled = false;
	bool setup = true;
	// ! Default values
	int hueValue = 180;
	int saturationValue = 50;
	int LuminanceValue = 50;

	//! x and y for mouse
	int x, y;

	//! Colour in RGB
	vec3 colour{ 255,255,255 };
	glm::vec3 buttonColour = { 200,150,100 };

	//! slider increment speed
	const int incrementSpeed = 5;
	//! slider width
	const int sliderWidth = 20;

	//! slider button size
	int buttonSize = 50;

	//! Location of slider
	const std::string GUILocations = "Resources\\Sprites\\GUI\\";

	//! Textures and buttons for slider
	
	Texture2D HueSlider;
	Texture2D SaturationSlider;
	Texture2D LuminanceSlider;
	Texture2D sliderIcon;

	Button IncrementHue;
	Button DecrementHue;
	Button IncrementSaturation;
	Button DecrementSaturation;
	Button IncrementLuminance;
	Button DecrementLuminance;
};

