#include "stdafx.h"
#include "ItemSelection.h"

std::map<int, ItemSelection&> ItemSelection::ItemSelectionWindows;

ItemSelection::ItemSelection(Inventory& inventory)
{
	this->inventoryPointer = &inventory;
	this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
}
ItemSelection::ItemSelection()
{
	this->imageLocation = "Resources\\UI\\CharacterSheet\\IconBorder.png";
}


ItemSelection::~ItemSelection()
{
}

void ItemSelection::CreateItemButtons(Inventory& inventory)
{
	float x = getPosition().x - getWidth() / 2 + iconSize;
	float y = getPosition().y - getHeight() / 2 + iconSize;
	totalItems = inventory.getCapacity();
	for (int i = 0; i < totalItems; i++)
	{
		Button newButton;

		// Start a new row
		if (x > getX() + getWidth() / 2 - iconSize)
		{
			x = getX() - getWidth() / 2 + iconSize;
			y += iconSize;
		}

		newButton.setPosition({ x, y });
		newButton.setSize(iconSize, iconSize);

		newButton.buttonItem = inventory.getStack(i);

		buttons.push_back(newButton);
		x += iconSize;
	}
	if (ID == -1)
	{
		ID = ItemSelectionWindows.size();
		ItemSelectionWindows.emplace(ID, *this);
	}
}
void ItemSelection::CreateItemSelection(Inventory& inventory)
{
	if(buttons.size() == 0 || totalItems != inventory.getCapacity())
		CreateItemButtons(inventory);
	bool anItemIsHovered = false;

	int mX, mY;
	SDL_GetMouseState(&mX, &mY);


	for (int i = 0; i < totalItems; i++)
	{
		// If item is clicked select it
		if (buttons[i].isPressed() && selected == -1)
		{
			selected = i;
			buttons[i].setSize(iconSize / 2, iconSize / 2);
		}

		// if selected
		if (selected == i)
		{
			SDL_GetMouseState(&mX, &mY);
			buttons[i].setPosition(mX, mY);
			buttons[i].setSize(iconSize / 2, iconSize / 2);
		}

		// Item Description
		if (buttons[i].isHovered() && buttons[i].buttonItem.size() > 0)
		{
			anItemIsHovered = true;
			itemDescription.showWindow = true;
			itemDescription.setPosition({ buttons[i].getX(), buttons[i].getY() + buttons[i].getSize().y });
			itemDescription.item = buttons[i].buttonItem.front();
		}
		if (selected >= 0)
		{
			if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				if (mX > getX() - (getWidth() / 2) && mX < getX() + (getWidth() / 2) && mY > getY() - (getHeight() / 2) && mY < getY() + (getHeight() / 2))		// If mouse is over this item slection then check to see where to put it
				{
					for (int j = 0; j < totalItems; j++)
					{
						//buttons[j].UpdateInfo();
						if (buttons[j].isPressed() && j != selected)
						{ // Place the item in that button
							if (buttons[j].buttonItem.size() == 0 && selected >= 0)
							{
								int itemToRemove = selected;
								buttons[j].buttonItem = buttons[selected].buttonItem;
								buttons[selected].buttonItem.clear();
								selected = -1;
								inventoryPointer->swap(selected, j);
								break;
							}
							else // Replace that item with the selected item
							{
								if (j != selected && selected >= 0)
								{
									Button temp; //store item
									temp = buttons[j];

									buttons[j] = buttons[selected]; // set item to selected
									buttons[selected] = temp;	// set selected to stored item
									selected = -1;
									break;
								}
							}
						}
					}
				}
			}
		}

	}
}

void ItemSelection::CreateItemButtons(std::vector<std::vector<std::shared_ptr<Item>>> items)
{
	//if (inventoryPointer != nullptr)
		//totalItems = inventoryPointer->getCapacity();
	buttons.clear();
	float x = getPosition().x - getWidth() / 2 + iconSize;
	float y = getPosition().y - getHeight() / 2 + iconSize;
	for (int i = 0; i < totalItems; i++)
	{
		Button newButton;

		// Start a new row
		if (x > getX() + getWidth() / 2 - iconSize)
		{
			x = getX() - getWidth() / 2 + iconSize;
			y += iconSize;
		}

		newButton.setPosition({ x, y });
		newButton.setSize(iconSize, iconSize);
		if (i < items.size())
			newButton.buttonItem = items[i];

		buttons.push_back(newButton);
		x += iconSize;
	}
	if (ID == -1)
	{
		ID = ItemSelectionWindows.size();
		ItemSelectionWindows.emplace(ID, *this);
	}
	l_inventorySize = items.size();
}

void ItemSelection::CreateItemSelection(std::vector<std::vector<std::shared_ptr<Item>>> items)
{
	// Get the inventory
	if (inventoryPointer != nullptr)
	{
		if (items.size() != inventoryPointer->getCapacity() || inventoryPointer->getCurrentSize() != l_inventorySize)
			CreateItemButtons(inventoryPointer->getItemList());
	}
	else if (items.size() != l_inventorySize)
		CreateItemButtons(items);
	//inventoryPointer = &inventory;


	bool anItemIsHovered = false;
	bool anyChangesMadeToInventory = false;
	bool changesToAnotherInventory = false;
	bool newStack = false;
	int mX, mY;
	SDL_GetMouseState(&mX, &mY);
	for (int i = 0; i < totalItems; i++)
	{

		//buttons[i].UpdateInfo();
		if (buttons.size() > 0)
		{
			// If item is clicked select it
			if (buttons[i].isPressed() && selected == -1)
			{
				selected = i;
				buttons[i].setSize(iconSize / 2, iconSize / 2);
			}

			// if selected
			if (selected == i)
			{
				SDL_GetMouseState(&mX, &mY);
				buttons[i].setPosition(mX, mY);
				buttons[i].setSize(iconSize / 2, iconSize / 2);
			}

			// Item Description
			if (buttons[i].isHovered() && buttons[i].buttonItem.size() > 0)
			{
				anItemIsHovered = true;
				itemDescription.showWindow = true;
				itemDescription.setPosition({ buttons[i].getX(), buttons[i].getY() + buttons[i].getSize().y });
				itemDescription.item = buttons[i].buttonItem.front();
			}



			if (selected >= 0)
			{
				if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					if (mX > getX() - (getWidth() / 2) && mX < getX() + (getWidth() / 2) && mY > getY() - (getHeight() / 2) && mY < getY() + (getHeight() / 2))		// If mouse is over this item slection then check to see where to put it
					{
						for (int j = 0; j < totalItems; j++)
						{
							//buttons[j].UpdateInfo();
							if (buttons[j].isPressed() && j != selected)
							{ // Place the item in that button

								if (buttons[j].buttonItem.size() == 0 && selected >= 0) //empty place
									inventoryPointer->swap(selected, j);
								else
									inventoryPointer->move(*inventoryPointer, selected, j);
								break;
							}
						}
					}
					else
					{
						// Place in another inventory
						for (auto& itemWindow : ItemSelectionWindows)
						{
							if (itemWindow.second.isOpen)
							{
								// If mouse is over one of the other itemSlectionWindows
								if (mX > itemWindow.second.getX() - (itemWindow.second.getWidth() / 2) && mX < itemWindow.second.getX() + (itemWindow.second.getWidth() / 2) && mY > itemWindow.second.getY() - (itemWindow.second.getHeight() / 2) && mY < itemWindow.second.getY() + (itemWindow.second.getHeight() / 2))		// If mouse is over this item slection then check to see where to put it
								{
									for (int j = 0; j < itemWindow.second.getTotalItems(); j++)
									{
										if (itemWindow.second.buttons[j].isPressed())	// Place the item in that button
										{
											if (itemWindow.second.buttons[j].buttonItem.size() == 0 && selected >= 0) // move to empty button
											{// new stack
												inventoryPointer->move(*itemWindow.second.inventoryPointer, selected, j);
												selected = -1;
											}
											// TODO:
												// if clicked on an existing button, tr
											// If that button has something in it and we have selected an item
											//else if (itemWindow.second.buttons[j].buttonItem.size() > 0 && selected >= 0 && buttons[selected].buttonItem.size() > 0)
											//{
											//	// If same item
											//	if (itemWindow.second.buttons[j].buttonItem.front()->getName() == buttons[selected].buttonItem.front()->getName())
											//	{
											//		// If there is enough space to add the two stacks
											//		if (itemWindow.second.buttons[j].buttonItem.size() + buttons[selected].buttonItem.size() < itemWindow.second.buttons[j].buttonItem.front()->getMaximumStackSize())
											//		{
											//			for (int i = 0; i < buttons[selected].buttonItem.size(); i++)
											//			{
											//				//itemWindow.second.buttons[j].buttonItem.push_back(buttons[selected].buttonItem[i]);
											//			}
											//			//buttons[selected].buttonItem.clear();
											//			break;
											//		}
											//		else
											//		{ // Set the stack size to max and create a new stack with the remainder
											//			int remainingStack = (itemWindow.second.buttons[j].buttonItem.size() + buttons[selected].buttonItem.size()) - itemWindow.second.buttons[j].buttonItem.front()->getMaximumStackSize();
											//			// Add remaining stack to inventory
											//			// Find an empty space
											//		}
											//		// Remove the selected item
											//		//buttons[selected].buttonItem = nullptr;
											//		selected = -1;
											//	}
											//}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		// Deselect
		if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_RIGHT))
			selected = -1;
		// Move to next position

	}
	if (!anItemIsHovered)
		itemDescription.showWindow = false;
}

void ItemSelection::Render(GL_Renderer& renderer)
{
	// only render if it has been created
	if (getPosition().x > 0 && getPosition().y > 0 && getSize().x > 0 && getSize().y > 0)
	{
		if (!isInitalised)
			Initalise();
		// Render this background
		renderer.RenderGUI(this->Background, this->position, this->size, this->rotation, this->transparency, this->colour, flipSprite);

		// Create and render items
		if (inventoryPointer != nullptr)
			CreateItemSelection(inventoryPointer->getItemList());

		// loop through each of the items
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].Render(renderer);

			if (selected == i)
				buttons[i].setSize(iconSize / 2, iconSize / 2);
			else
				buttons[i].setSize(iconSize, iconSize);
			if (buttons[i].isPressed())
				selected = i;



			// Render the item on top of the button
			if (buttons[i].buttonItem.size() > 0)
			{

				buttons[i].buttonItem.front()->icon.setPosition(buttons[i].getPosition());
				buttons[i].buttonItem.front()->icon.setSize(buttons[i].getSize() / 1.3f);
				buttons[i].buttonItem.front()->icon.Render(renderer);
			}

			// Item Stack number

			if (buttons[i].buttonItem.size() > 0)
			{
				renderer.RenderText(std::to_string(buttons[i].buttonItem.size()), buttons[i].buttonItem.front()->icon.getPosition() + (buttons[i].buttonItem.front()->icon.getSize() / 3.0f), buttons[i].getSize() / 5.0f, { 0.2f, 0.2f }, { 100,100,100 });
			}
		}


		if (itemDescription.showWindow)
			itemDescription.Render(renderer);
	}
}
