#pragma once
#include "GUI.h"
class SpeechBubble : public GUI
{
public:
	SpeechBubble::SpeechBubble();

	SpeechBubble::~SpeechBubble();

	//! Text size
	float textSize = 0.2f;

	std::string text;

	void Render(GL_Renderer& renderer);
};

