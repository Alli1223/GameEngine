#include "WorldEditor.h"



WorldEditor::WorldEditor()
{
	this->window.setPosition(300, 400);
	this->window.setSize(500, 500);
	this->window.transparency = 0.5;
}


WorldEditor::~WorldEditor()
{
}
void WorldEditor::CreateExampleCells()
{
	cellHighlight.Sprite = ResourceManager::LoadTexture("Resources\\Sprites\\GUI\\LuminanceSlider.png");
	cellHighlight.transparency = 0.5f;
	cellHighlight.renderLayer = 4;
	for (int i = 0; i < cellNames.size(); i++)
	{
		Cell cell;
		Button button;
		cell.AssignType(0, cellNames[i]);
		exampleCells.push_back(cell);
		window.buttons.push_back(button);
	}
	selected = -1; // reset selection
	initalisedCells = true;
}

void WorldEditor::CreateExampleSheet(GameWindow& window, std::string spriteSheetName, int totalSprites, glm::vec2 position, glm::vec2 size)
{
	window.isOpen = true;
	window.setPosition(position);
	window.setSize(size);
	exampleCells.erase(exampleCells.begin(), exampleCells.end());
	cellNames.erase(cellNames.begin(), cellNames.end());
	for (int i = 0; i < totalSprites; i++)
		cellNames[i] = spriteSheetName + std::to_string(i);
	CreateExampleCells();
}

void WorldEditor::Render(GL_Renderer& renderer, World& world, Player& player)
{
	// Get mosue position
	int X = 0, Y = 0;
	float mX = 0, mY = 0;
	int cellSize = world.getCellSize();

	mX = (X + renderer.camera.getX() + (cellSize / 2)) / cellSize;
	mY = (Y + renderer.camera.getY() + (cellSize / 2)) / cellSize;

	// Create cells
	if (!initalisedCells)
		CreateExampleCells();
	if (this->window.isOpen)
	{
		window.Render(renderer);


		float x = this->window.getPosition().x - this->window.getWidth() / 2 + iconSize;
		float y = this->window.getPosition().y - this->window.getHeight() / 2 + iconSize;

		for (int i = 0; i < exampleCells.size(); i++)
		{
			if (x > this->window.getX() + this->window.getWidth() / 2 - iconSize)
			{
				x = this->window.getX() - this->window.getWidth() / 2 + iconSize;
				y += iconSize;
			}
			this->window.buttons[i].Background = exampleCells[i].Sprite;
			if (exampleCells[i].layerdSprite.Width > 0)
				this->window.buttons[i].Background = exampleCells[i].layerdSprite;
			this->window.buttons[i].setPosition({ x, y });
			this->window.buttons[i].setSize(iconSize, iconSize);
			if (selected == i)
				this->window.buttons[i].setSize(iconSize / 2, iconSize / 2);

			if (this->window.buttons[i].isPressed())
			{
				selected = i;
				this->window.buttons[i].setSize(iconSize / 2, iconSize / 2);
			}
			this->window.buttons[i].Render(renderer);
			x += iconSize;
		}
		// If an item is selected
		if (selected >= 0)
		{
			int X = 0, Y = 0;
			SDL_GetMouseState(&X, &Y);

			mX = (X + renderer.camera.getX() + (cellSize / 2)) / cellSize;
			mY = (Y + renderer.camera.getY() + (cellSize / 2)) / cellSize;
			

			// If the mouse is ouside of the box
			if (X > window.getX() - (window.getWidth() / 2) && X < window.getX() + (window.getWidth() / 2) && Y > window.getY() - (window.getHeight() / 2) && Y < window.getY() + (window.getHeight() / 2))
			{

			}
			else // Inside the box
			{
				cellHighlight.setPosition(mX * cellSize, mY * cellSize);
				cellHighlight.setSize(cellSize, cellSize);

				cellHighlight.Render(renderer);

				// Place the cell if they click the ground
				// Place on lower layer
				if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					if (X > this->window.getX() + (this->window.getWidth() / 2) || X < this->window.getX() - (this->window.getWidth() / 2) || Y > this->window.getY() - (this->window.getHeight() / 2))	// make sure not to place tile under the window
					{
						if (placementArea > 1)
							for (int xp = -placementArea; xp < placementArea; xp++)
								for (int yp = -placementArea; yp < placementArea; yp++)
								{
									world.GetCell(mX + xp, mY + yp)->AssignType(0, cellNames[selected]);
									world.updatedCells.push_back(world.GetCell(mX * xp, mY * yp));
								}
						else
						{
							world.GetCell(mX, mY)->AssignType(1, cellNames[selected]);
							world.updatedCells.push_back(world.GetCell(mX, mY));
							std::cout << "Updating cell: " << world.GetCell(mX, mY)->getX() << " " << world.GetCell(mX, mY)->getY() << " -- mouse Pos: " << mX << " " << mY << std::endl;
						}
					}
				}
				if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
				{
					world.GetCell(mX, mY)->Clear();
				}
				// Place on upper layer
				if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					if (X > this->window.getX() + (this->window.getWidth() / 2))	// make sure not to place tile under the window
					{
						if (placementArea > 1)
							for (int xp = 0; xp < placementArea; xp++)
								for (int yp = 0; yp < placementArea; yp++)
								{
									world.GetCell(mX * xp, mY * yp)->AssignType(1, cellNames[selected]);
									world.updatedCells.push_back(world.GetCell(mX * xp, mY * yp));
								}
						else
						{
							world.GetCell(mX, mY)->AssignType(1, cellNames[selected]);
							world.updatedCells.push_back(world.GetCell(mX, mY));
						}
					}
				}
			}
		}
	}


	ImGui::Begin("Editor");

	ImGui::Checkbox("Open / Close", &this->window.isOpen);


	// Opens the spritesheets
	if (ImGui::TreeNode("Sprite Sheets"))
	{
		if (ImGui::TreeNode("Ground tiles"))
		{
			if (ImGui::Button("Autumn", { 100, 50 }))
			{
				iconSize = 25;
				CreateExampleSheet(window, "Autumn_Ground_", 28 * 9, { 500,400 }, { 725,200 });
			}
			if (ImGui::IsItemHovered())
				selected = -1;
			ImGui::SameLine();
			if (ImGui::Button("Spring", { 100, 50 }))
			{
				iconSize = 25;
				CreateExampleSheet(window, "Spring_Ground_", 28 * 9, { 500,400 }, { 725,200 });
			}
			if (ImGui::IsItemHovered())
				selected = -1;
			if (ImGui::Button("Summer", { 100, 50 }))
			{
				iconSize = 25;
				CreateExampleSheet(window, "Summer_Ground_", 21 * 9, { 500,400 }, { 550,200 });
			}
			if (ImGui::IsItemHovered())
				selected = -1;
			ImGui::SameLine();
			if (ImGui::Button("Winter", { 100, 50 }))
			{
				iconSize = 25;
				CreateExampleSheet(window, "Winter_Ground_", 35 * 9, { 500,400 }, { 875,200 });
			}
			if (ImGui::Button("Water", { 100, 50 }))
			{
				iconSize = 50;
				window.isOpen = true;
				window.setPosition(200, 200);
				window.setWidth(980);
				window.setSize(63 * 3 + 50, 400);
				exampleCells.erase(exampleCells.begin(), exampleCells.end());
				cellNames.erase(cellNames.begin(), cellNames.end());

				int j = 0, c = 0;
				for (int k = 0; k < 6; k++)
				{
					for (int i = 0; i < 3; i++)
						cellNames[c] = "water_spriteSheet_" + std::to_string(i + j), c++;
					j += 18;
				}
				CreateExampleCells();
			}
			ImGui::SameLine();
			if (ImGui::Button("Roguelike", { 100, 50 }))
			{
				iconSize = 20;
				if (ImGui::IsItemHovered())
					selected = -1;
				window.isOpen = true;
				window.setPosition(700, 500);
				window.setSize(1170, 800);
				exampleCells.erase(exampleCells.begin(), exampleCells.end());
				cellNames.erase(cellNames.begin(), cellNames.end());
				for (int i = 0; i < 1730; i++)
					cellNames[i] = "Roguelike_" + std::to_string(i);
				CreateExampleCells();
			}
			if (ImGui::IsItemHovered())
				selected = -1;
			ImGui::TreePop();
		}

		// Surface sprites
		if (ImGui::TreeNode("Surface Sprites"))
		{
			if (ImGui::Button("Rocks", { 100, 50 }))
			{
				iconSize = 50;
				window.isOpen = true;
				window.setPosition(300, 400);
				exampleCells.erase(exampleCells.begin(), exampleCells.end());
				cellNames.erase(cellNames.begin(), cellNames.end());
				for (int i = 0; i < 5 * 6; i++)
					cellNames[i] = "Rock_" + std::to_string(i);
				CreateExampleCells();
			}
			if (ImGui::IsItemHovered())
				selected = -1;



			if (ImGui::Button("Paths", { 100, 50 }))
			{
				iconSize = 50;
				window.isOpen = true;
				window.setPosition(300, 400);
				window.setWidth(300);
				exampleCells.erase(exampleCells.begin(), exampleCells.end());
				cellNames.erase(cellNames.begin(), cellNames.end());
				for (int i = 0; i < 5 * 11; i++)
					cellNames[i] = "Path_" + std::to_string(i);
				CreateExampleCells();
			}
			if (ImGui::IsItemHovered())
				selected = -1;
			ImGui::SameLine();


			if (ImGui::Button("rpg", { 100, 50 }))
			{
				iconSize = 20;
				if (ImGui::IsItemHovered())
					selected = -1;
				window.isOpen = true;
				window.setPosition(700, 500);
				window.setSize(1170, 800);
				exampleCells.erase(exampleCells.begin(), exampleCells.end());
				cellNames.erase(cellNames.begin(), cellNames.end());
				for (int i = 0; i < 1730; i++)
					cellNames[i] = "RpgSprites_" + std::to_string(i);
				CreateExampleCells();
			}
			if (ImGui::IsItemHovered())
				selected = -1;

			if (ImGui::Button("flowers", { 100, 50 }))
			{
				iconSize = 50;
				if (ImGui::IsItemHovered())
					selected = -1;
				window.isOpen = true;
				window.setPosition(600, 600);
				window.setSize(800, 800);
				exampleCells.erase(exampleCells.begin(), exampleCells.end());
				cellNames.erase(cellNames.begin(), cellNames.end());
				for (int i = 0; i < 256; i++)
					cellNames[i] = "Flowers_" + std::to_string(i);
				CreateExampleCells();
			}
			if (ImGui::IsItemHovered())
				selected = -1;
			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
	ImGui::SliderInt("Area", &placementArea, 0, 5, "%d");

	// Get light selection
	if (ImGui::TreeNode("Lights"))
	{
		if (ImGui::Button("StreetLight", { 100, 50 }))
		{
			selectedLight = 0;
		}
		if (ImGui::Button("CampFire", { 100, 50 }))
		{
			selectedLight = 1;
		}
		if (ImGui::Button("Torch", { 100, 50 }))
		{
			selectedLight = 2;
		}

		ImGui::TreePop();
	}
	// Place light
	if (selectedLight >= 0)
	{
		SDL_GetMouseState(&X, &Y);
		mX = (X + renderer.camera.getX() + (cellSize / 2)) / cellSize;
		mY = (Y + renderer.camera.getY() + (cellSize / 2)) / cellSize;
		if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			// Streetlight
			if (selectedLight == 0)
			{
				std::string streetLight = "StreetLight";
				world.GetCell(mX, mY)->AssignType(2, streetLight);
				selectedLight = -1;
			}
			// Campfire
			else if (selectedLight == 1)
			{
				std::string streetLight = "CampFire";
				world.GetCell(mX, mY)->AssignType(1, streetLight);
				selectedLight = -1;
			}
			// Campfire
			else if (selectedLight == 2)
			{
				std::string torch = "Torch";
				world.GetCell(mX, mY)->AssignType(1, torch);
				selectedLight = -1;
			}
		}
	}

	ImGui::Checkbox("Place Grass", &placeGrass);
	if (placeGrass)
	{
		placeFerns = false;
		if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			mX = (X + renderer.camera.getX() + (cellSize / 2)) / cellSize;
			mY = (Y + renderer.camera.getY() + (cellSize / 2)) / cellSize;
			std::string vegSting = "LongGrass";
			if (world.GetCell(mX, mY)->vegetation.size() < 5)
				world.GetCell(mX, mY)->AssignType(1, vegSting);
		}
	}
	ImGui::SameLine();
	ImGui::Checkbox("Place Fern", &placeFerns);
	if (placeFerns)
	{
		placeGrass = false;
		if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			mX = (X + renderer.camera.getX() + (cellSize / 2)) / cellSize;
			mY = (Y + renderer.camera.getY() + (cellSize / 2)) / cellSize;
			std::string vegSting = "Fern";
			if (world.GetCell(mX, mY)->vegetation.size() < 1)
				world.GetCell(mX, mY)->AssignType(1, vegSting);
		}
	}

	if (ImGui::Button("Place NPC House", { 100, 50 }))
	{
		PlaceHosue = true;
	}
	if (PlaceHosue)
	{
		if (SDL_GetMouseState(&X, &Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			NPCHouse house;
			house.setPosition(X + renderer.camera.getX(), Y + renderer.camera.getY());
			house.CreateOccupants(5);

			world.buildings.push_back(house.getSharedPointer());

			PlaceHosue = false;
		}


	}

	//selectedLight = -1;
	ImGui::End();
}


