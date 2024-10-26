#include "stdafx.h"
#include "Villager.h"
#include "PathFinder.h"

Villager::Villager()
{
	Pathfinder pf;
	pathfinder = std::make_shared<Pathfinder>(pf);
	this->renderLayer = 3;
	this->setSize(100, 100);
	this->ID = rand() % 999999999;
	playerLight.lightType = LightSource::LightType::npcAmbientLight;
	playerLight.isOn = false;
}


Villager::~Villager()
{
}

void Villager::GenerateVillager()
{
	// Randomise the body remove when we have menu
	srand(time(NULL));
	this->body.eyeType = Body::EyeType(rand() % 13);
	this->body.earType = Body::EarType(rand() % 10);
	this->body.hairType = Body::HairType(rand() % 8);
	this->body.gender = Body::Gender(rand() % 2);
	this->CharacterClothes.body = Clothing::BodyWear(rand() % 4);
	this->CharacterClothes.leg = Clothing::LegWear(rand() % 4);
	this->money = rand() % 50;
	s_action = ShopActions::browsing;
}


void Villager::Update()
{
	if (isSelected)
	{
		
	}
	// IF the player in in a building
	if (isInShop)
	{
		switch (s_action)
		{
			// Choose random spot in room to walk to
		case ShopActions::browsing:
			//this->path = pathfinder->findPathThread(world, this->getPosition() / (float)world.playerShop.getTileSize(), { rand() % 5, rand() % 5 }, isInShop);
			break;
			// Walk to the exit
		case ShopActions::exiting:
			//this->path = pathfinder->findPathThread(world, this->getPosition() / (float)world.getCellSize(), world.playerShop.entrance.getPosition() / (float)world.getCellSize(), isInShop);
			break;
		}
	}
	// In the World
	else
	{
		// Choose an action the NPC is doing
		switch (w_action)
		{
		default:
			break;
		case WorldActions::toShop:
			if (path.size() == 0) // create the path
			{
			//	this->path = pathfinder->findPathThread(world, this->getPosition() / (float)world.getCellSize(), world.playerShop.entrance.getPosition() / (float)world.getCellSize(), isInShop);
			}
			break;
		case WorldActions::wondering:
			if (path.size() == 0) // create the path
			{
				vec2 randPos = { (rand() % 20) - 10, (rand() % 20) - 10 };
				//this->path = pathfinder->findPathThread(world, this->getPosition() / (float)world.getCellSize(), randPos, isInShop);
			}
			break;
		}
	}
}

void Villager::Render(GL_Renderer& renderer)
{

	//if (!hasPhysics)
	//{
	//	setSize({ getSize().x / 2.0f, getSize().y });
	//	//InitPhysics(renderer.p_World.get(), b2BodyType::b2_dynamicBody, 1.0f, 0.3f);
	//	setSize({ getSize().x * 2.0f, getSize().y });
	//}
	I_renderer = &renderer;
	this->setPosition({ this->getBody()->GetPosition().x * physicsScaleUp,this->getBody()->GetPosition().y * physicsScaleUp });
	getBody()->SetLinearDamping(2000.0f); // dont let the player gradually increase speed

	if (isPlayerMoving())
	{
		walkHorizontalAnimation.OnAnimate();
		walkVerticalAnimation.OnAnimate();
		blink = false;
	}
	else
	{
		walkHorizontalAnimation.setCurrentFrame(0);
		walkVerticalAnimation.setCurrentFrame(0);
		// Blinking when idle
		if (blinkSpeed.getTicks() > blinkFrequency)
		{
			if (!blink)
				blink = true;
			if (blinkSpeed.getTicks() > blinkFrequency + blinkDuration)
				blinkSpeed.restart();
		}
		else
			blink = false;

		// What a mess
		if (idleAnimationTimer.getTicks() > 10000)
		{
			legFlipIdleAnimation.setStartIndex(36);
			legFlipIdleAnimation.OnAnimate();
			if (idleAnimationTimer.getTicks() > 11000)
			{
				idleAnimationTimer.restart();
				legFlipIdleAnimation.setCurrentFrame(0);
			}

		}
		else
			legFlipIdleAnimation.setStartIndex(32);
	}

	//Assign sprites
	RotateCharacter(renderer);
	//RenderBody(0);

	// if selected
	glm::ivec2 mPos;
	if (SDL_GetMouseState(&mPos.x, &mPos.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		isSelected = false;
		if ((mPos.x + renderer.camera.getPosition().x > getPosition().x - getHalfSize().x) && (mPos.x + renderer.camera.getPosition().x < getPosition().x + getHalfSize().x))
		{
			if ((mPos.y + renderer.camera.getPosition().y > getPosition().y - getHalfSize().y) && (mPos.y + renderer.camera.getPosition().y < getPosition().y + getHalfSize().y))
			{
				isSelected = true;
			}
		}
		
	}
	if (isSelected)
	{
		renderer.RenderOutline(this->nakedBody, this->position, this->size, this->rotation, this->transparency, this->bodyColour, this->flipSprite);
	}
	speechBubble.text = std::to_string(this->getTargetRotation());
	speechBubble.setPosition(getPosition());
	speechBubble.Render(renderer);

}



void Villager::RenderBody(int index)
{
	switch (body.gender)
	{
		// MALE BODY TYPE
	case Body::Gender::male:
		nakedBody = ResourceManager::GetAtlasTexture("maleBasic", index);
		NormalMap = ResourceManager::GetAtlasTexture("maleBasic_normal", index);
		break;
		// FEMALE BODY TYPE 
	case Body::Gender::female:
		nakedBody = ResourceManager::GetAtlasTexture("femaleBasic", index);
		NormalMap = ResourceManager::GetAtlasTexture("femaleBasic_normal", index);
		break;
	}

	switch (body.hairType)
	{
	case Body::HairType::hair1:
		hair = ResourceManager::GetAtlasTexture("Hair1", index);
		break;
	case Body::HairType::hair2:
		hair = ResourceManager::GetAtlasTexture("Hair2", index);
		break;
	case Body::HairType::hair3:
		hair = ResourceManager::GetAtlasTexture("Hair3", index);
		break;
	case Body::HairType::hair4:
		hair = ResourceManager::GetAtlasTexture("Hair4", index);
		break;
	case Body::HairType::hair5:
		hair = ResourceManager::GetAtlasTexture("Hair5", index);
		break;
	case Body::HairType::hair6:
		hair = ResourceManager::GetAtlasTexture("Hair6", index);
		break;
	case Body::HairType::hair7:
		hair = ResourceManager::GetAtlasTexture("Hair6", index);
		break;
	case Body::HairType::hair8:
		hair = ResourceManager::GetAtlasTexture("Hair8", index);
		break;
	}

	switch (body.eyeType)
	{
	case Body::EyeType::eye1:
		eyes = ResourceManager::GetAtlasTexture("Eye1", index);
		break;
	case Body::EyeType::eye2:
		eyes = ResourceManager::GetAtlasTexture("Eye2", index);
		break;
	case Body::EyeType::eye3:
		eyes = ResourceManager::GetAtlasTexture("Eye3", index);
		break;
	case Body::EyeType::eye4:
		eyes = ResourceManager::GetAtlasTexture("Eye4", index);
		break;
	case Body::EyeType::eye5:
		eyes = ResourceManager::GetAtlasTexture("Eye5", index);
		break;
	case Body::EyeType::eye6:
		eyes = ResourceManager::GetAtlasTexture("Eye6", index);
		break;
	case Body::EyeType::eye7:
		eyes = ResourceManager::GetAtlasTexture("Eye7", index);
		break;
	case Body::EyeType::eye8:
		eyes = ResourceManager::GetAtlasTexture("Eye8", index);
		break;
	case Body::EyeType::eye9:
		eyes = ResourceManager::GetAtlasTexture("Eye9", index);
		break;
	case Body::EyeType::eye10:
		eyes = ResourceManager::GetAtlasTexture("Eye10", index);
		break;
	case Body::EyeType::eye11:
		eyes = ResourceManager::GetAtlasTexture("Eye11", index);
		break;
	case Body::EyeType::eye12:
		eyes = ResourceManager::GetAtlasTexture("Eye12", index);
		break;
	case Body::EyeType::eye13:
		eyes = ResourceManager::GetAtlasTexture("Eye13", index);
		break;
	}


	switch (body.earType)
	{
	case Body::aquatic:
		ears = ResourceManager::GetAtlasTexture("aquatic", index);
		break;
	case Body::cat1:
		ears = ResourceManager::GetAtlasTexture("cat1", index);
		break;
	case Body::cat2:
		ears = ResourceManager::GetAtlasTexture("cat2", index);
		break;
	case Body::EarType::elf1:
		ears = ResourceManager::GetAtlasTexture("elf1", index);
		break;
	case Body::EarType::elf2:
		ears = ResourceManager::GetAtlasTexture("elf2", index);
		break;
	case Body::EarType::elf3:
		ears = ResourceManager::GetAtlasTexture("elf3", index);
		break;
	case Body::EarType::elf4:
		ears = ResourceManager::GetAtlasTexture("elf4", index);
		break;
	case Body::EarType::elf5:
		ears = ResourceManager::GetAtlasTexture("elf5", index);
		break;
	case Body::EarType::elf6:
		ears = ResourceManager::GetAtlasTexture("elf6", index);
		break;
	case Body::EarType::human:
		ears = ResourceManager::GetAtlasTexture("human", index);
		break;
	}

	switch (CharacterClothes.body)
	{
	case Clothing::BodyWear::femaleTop1:
		top = ResourceManager::GetAtlasTexture("FemaleTop_1", index);
		break;
	case Clothing::BodyWear::femaleTop2:
		top = ResourceManager::GetAtlasTexture("FemaleTop_2", index);
		break;
	case Clothing::BodyWear::maleTop1:
		top = ResourceManager::GetAtlasTexture("MaleTop_1", index);
		break;
	case Clothing::BodyWear::maleTop2:
		top = ResourceManager::GetAtlasTexture("MaleTop_2", index);
		break;
	}
	switch (CharacterClothes.leg)
	{
	case Clothing::LegWear::femaleBottom1:
		bottom = ResourceManager::GetAtlasTexture("FemaleBottom_1", index);
		break;
	case Clothing::LegWear::femaleBottom2:
		bottom = ResourceManager::GetAtlasTexture("FemaleBottom_2", index);
		break;
	case Clothing::LegWear::maleBottom1:
		bottom = ResourceManager::GetAtlasTexture("MaleBottom_1", index);
		break;
	case Clothing::LegWear::maleBottom2:
		bottom = ResourceManager::GetAtlasTexture("MaleBottom_2", index);
		break;
	}
}

void Villager::UpdatePathPosition()
{
	// If the agent has a path
	if (path.size() > 0)
	{
		glm::ivec2 agentCellPos = getPosition()  / 100.0f;
		// if the agent has reached the next point, iterate
		if (pathfinder->pathPointIterator < path.size())
			if (agentCellPos == path[pathfinder->pathPointIterator])
			{
				if (agentCellPos == path[path.size() - 1]) // reached the goal
					path.clear(), pathfinder->pathPointIterator = 0;
				else
					pathfinder->pathPointIterator++;
			}
			else // move towards that point
			{
				glm::vec2 pathPos = path[pathfinder->pathPointIterator];
				vec2 thisPos = this->getPosition() + (getSize().x / 2.0f);
				pathPos *= 100.0f;

				// Distance to destination from this position - path position
				float deltaX = agentCellPos.x - (path[pathfinder->pathPointIterator].x);
				float deltaY = agentCellPos.y - (path[pathfinder->pathPointIterator].y);
				float length = sqrt(deltaX * deltaX + deltaY * deltaY);
				// Normalize 
				deltaX /= length;
				deltaY /= length;
				float angleInDegrees = atan2(deltaY, deltaX) * 180.0 / PI;

				// Apply correction to rotation
				///this->rotation = angleInDegrees + 90;

				// Multiply direction by magnitude 
				deltaX *= walkSpeed;
				deltaY *= walkSpeed;

				deltaX *= -1.0f;
				deltaY *= -1.0f;


				getBody()->ApplyForceToCenter(b2Vec2(deltaX, deltaY), true);
				this->setPlayerMoving(true);
				this->setTargetRotation(angleInDegrees);
			}
	}
}
