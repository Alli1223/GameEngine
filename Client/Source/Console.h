#pragma once
#include "GUI.h"
#include "GameSettings.h"
class Console : public GUI
{
public:
	void Init(GameSettings& gs);
	static void Print(std::string text);

	//! Render this GUI object
	void Render(GL_Renderer& renderer);

	//! Show console
	bool showConsole = true;
private:
	static std::vector<std::string> textLog;
	float textSize = 0.2f;
	float transparency = 0.8f;

};