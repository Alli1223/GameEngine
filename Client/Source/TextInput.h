#pragma once
#include "stdafx.h"
#include "GUI.h"
class TextInput :  public GUI
{
public:
	std::string inputText;
	void Update();

	void Render(GL_Renderer& renderer);

private:
	bool isSelected = false;
	bool renderText = false;

	//! Text size
	float textSize = 0.2f;

	int mouseX, mouseY;
};

