#include "stdafx.h"
#include "TextInput.h"

void TextInput::Update()
{
	if (!initilised)
		Init();
	if (isMouseOver())
	{
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			isSelected = true;
		}
	}
	else
		isSelected = false;
	if (isSelected)
	{
		//Event handler
		SDL_Event e;
		//Enable text input
		SDL_StartTextInput();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				isSelected = false;
			}
			//Special key input
			else if (e.type == SDL_KEYDOWN)
			{
				//Handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					//lop off character
					inputText.pop_back();
					renderText = true;
				}
				//Handle copy
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				//Handle paste
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText = SDL_GetClipboardText();
					renderText = true;
				}
			}
			//Special text input event
			else if (e.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
				{
					//Append character
					inputText += e.text.text;
					renderText = true;
				}
			}
		}
	}
	else {
		//Disable text input
		//SDL_StopTextInput();
	}
}

void TextInput::Render(GL_Renderer& renderer)
{
	if (isSelected)
		this->setTransparency(1.0f);
	else
		this->setTransparency(0.5f);
	renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);
	if(renderText && inputText.size() > 0)
		renderer.RenderText(inputText, { this->position.x - getWidth() / 2 + 20, position.y + getHeight() / 4}, this->size, { textSize, textSize }, { 0,0,0 });
}

bool TextInput::fieldSelected()
{
	if (isSelected)
		return true;

	return false;
}

void TextInput::Init()
{
	this->Background = ResourceManager::LoadTexture("Resources\\UI\\Windows\\panel1.png");
}

