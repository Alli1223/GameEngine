#pragma once
#include "stdafx.h"
#include "GUI.h"
class TextInput :  public GUI
{
public:

	//! String of text that the user has entered
	std::string inputText;
	
	//! Update the text
	void Update();

	//! Render the text
	void Render(GL_Renderer& renderer);

	//! initilise

	void Init();

private:

	//! If the text box is selected
	bool isSelected = false;

	//! Whether to render the text
	bool renderText = false;

	//! Text size
	float textSize = 0.30f;

	bool initilised = false;

};

