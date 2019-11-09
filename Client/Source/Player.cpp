#include "stdafx.h"
#include "player.h"
#include "PathFinder.h"
void Player::LoadResources()
{
	// Bodies
	ResourceManager::LoadAtlas("maleBasic", CharacterDirectory + "Male\\MaleBasic.png", 9, 63);
	ResourceManager::LoadAtlas("femaleBasic", CharacterDirectory + "Female\\FemaleBasic.png", 9, 63);
	ResourceManager::LoadAtlas("maleBasic_normal", CharacterDirectory + "Male\\MaleBasic_normal.png", 9, 63);
	ResourceManager::LoadAtlas("femaleBasic_normal", CharacterDirectory + "Female\\FemaleBasic_normal.png", 9, 63);
	// Animations
	ResourceManager::LoadAtlas("maleFishing", CharacterDirectory + "Male\\MaleFishing.png", 6, 63);
	ResourceManager::LoadAtlas("femaleFishing", CharacterDirectory + "Female\\FemaleFishing.png", 6, 63);
	// HAIR
	ResourceManager::LoadAtlas("Hair1", PlayerAccessoriesDirectory + "Hair\\Hair_1.png", 9, 63);
	ResourceManager::LoadAtlas("Hair2", PlayerAccessoriesDirectory + "Hair\\Hair_2.png", 9, 63);
	ResourceManager::LoadAtlas("Hair3", PlayerAccessoriesDirectory + "Hair\\Hair_3.png", 9, 63);
	ResourceManager::LoadAtlas("Hair4", PlayerAccessoriesDirectory + "Hair\\Hair_4.png", 9, 63);
	ResourceManager::LoadAtlas("Hair5", PlayerAccessoriesDirectory + "Hair\\Hair_5.png", 9, 63);
	ResourceManager::LoadAtlas("Hair6", PlayerAccessoriesDirectory + "Hair\\Hair_6.png", 9, 63);
	ResourceManager::LoadAtlas("Hair7", PlayerAccessoriesDirectory + "Hair\\Hair_7.png", 9, 63);
	ResourceManager::LoadAtlas("Hair8", PlayerAccessoriesDirectory + "Hair\\Hair_8.png", 9, 63);
	// EYES
	ResourceManager::LoadAtlas("Eye1", PlayerAccessoriesDirectory + "Eyes\\Eye_type_1.png", 9, 63);
	ResourceManager::LoadAtlas("Eye2", PlayerAccessoriesDirectory + "Eyes\\Eye_type_2.png", 9, 63);
	ResourceManager::LoadAtlas("Eye3", PlayerAccessoriesDirectory + "Eyes\\Eye_type_3.png", 9, 63);
	ResourceManager::LoadAtlas("Eye4", PlayerAccessoriesDirectory + "Eyes\\Eye_type_4.png", 9, 63);
	ResourceManager::LoadAtlas("Eye5", PlayerAccessoriesDirectory + "Eyes\\Eye_type_5.png", 9, 63);
	ResourceManager::LoadAtlas("Eye6", PlayerAccessoriesDirectory + "Eyes\\Eye_type_6.png", 9, 63);
	ResourceManager::LoadAtlas("Eye7", PlayerAccessoriesDirectory + "Eyes\\Eye_type_7.png", 9, 63);
	ResourceManager::LoadAtlas("Eye8", PlayerAccessoriesDirectory + "Eyes\\Eye_type_8.png", 9, 63);
	ResourceManager::LoadAtlas("Eye9", PlayerAccessoriesDirectory + "Eyes\\Eye_type_9.png", 9, 63);
	ResourceManager::LoadAtlas("Eye10", PlayerAccessoriesDirectory + "Eyes\\Eye_type_10.png", 9, 63);
	ResourceManager::LoadAtlas("Eye11", PlayerAccessoriesDirectory + "Eyes\\Eye_type_11.png", 9, 63);
	ResourceManager::LoadAtlas("Eye12", PlayerAccessoriesDirectory + "Eyes\\Eye_type_12.png", 9, 63);
	ResourceManager::LoadAtlas("Eye13", PlayerAccessoriesDirectory + "Eyes\\Eye_type_13.png", 9, 63);
	// EARS
	ResourceManager::LoadAtlas("aquatic", PlayerAccessoriesDirectory + "Ears\\Aquatic_Ears.png", 9, 63);
	ResourceManager::LoadAtlas("cat1", PlayerAccessoriesDirectory + "Ears\\Cat_Ears_1.png", 9, 63);
	ResourceManager::LoadAtlas("cat2", PlayerAccessoriesDirectory + "Ears\\Cat_Ears_2.png", 9, 63);
	ResourceManager::LoadAtlas("elf1", PlayerAccessoriesDirectory + "Ears\\Elf_Ears_1.png", 9, 63);
	ResourceManager::LoadAtlas("elf2", PlayerAccessoriesDirectory + "Ears\\Elf_Ears_2.png", 9, 63);
	ResourceManager::LoadAtlas("elf3", PlayerAccessoriesDirectory + "Ears\\Elf_Ears_3.png", 9, 63);
	ResourceManager::LoadAtlas("elf4", PlayerAccessoriesDirectory + "Ears\\Elf_Ears_4.png", 9, 63);
	ResourceManager::LoadAtlas("elf5", PlayerAccessoriesDirectory + "Ears\\Elf_Ears_5.png", 9, 63);
	ResourceManager::LoadAtlas("elf6", PlayerAccessoriesDirectory + "Ears\\Elf_Ears_6.png", 9, 63);
	ResourceManager::LoadAtlas("human", PlayerAccessoriesDirectory + "Ears\\Human_Ears.png", 9, 63);

	// CLOTHES
	// Male clothes
	ResourceManager::LoadAtlas("MaleTop_1", CharacterClothingDirectory + "Male\\Tops\\Male_top_1.png", 9, 63);
	ResourceManager::LoadAtlas("MaleTop_2", CharacterClothingDirectory + "Male\\Tops\\Male_top_2.png", 9, 63);
	ResourceManager::LoadAtlas("MaleBottom_1", CharacterClothingDirectory + "Male\\Bottoms\\Male_bottoms_1.png", 9, 63);
	ResourceManager::LoadAtlas("MaleBottom_2", CharacterClothingDirectory + "Male\\Bottoms\\Male_bottoms_2.png", 9, 63);

	// Female clothes
	ResourceManager::LoadAtlas("FemaleTop_1", CharacterClothingDirectory + "Female\\Tops\\Female_top_1.png", 9, 63);
	ResourceManager::LoadAtlas("FemaleTop_2", CharacterClothingDirectory + "Female\\Tops\\Female_top_2.png", 9, 63);
	ResourceManager::LoadAtlas("FemaleBottom_1", CharacterClothingDirectory + "Female\\Bottoms\\Female_Bottoms_1.png", 9, 63);
	ResourceManager::LoadAtlas("FemaleBottom_2", CharacterClothingDirectory + "Female\\Bottoms\\Female_Bottoms_2.png", 9, 63);
}


//////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR
/////////////////////////////////////////////////////////////////////////
Player::Player() : colisionIdentity(CollisionIdentifier::CollisionEntityTypes::player)
{
	// Load the sprite atlases
	LoadResources();

	// Animations setup
	walkHorizontalAnimation.maxFrames = 4;
	walkVerticalAnimation.maxFrames = 6;
	legFlipIdleAnimation.maxFrames = 3;
	fishingCast.maxFrames = 4;
	fishingReel.maxFrames = 6;
	fishingCast.runOnce = true;
	fishingReel.runOnce = true;
	legFlipIdleAnimation.setFrameRate(500);
	walkVerticalAnimation.setFrameRate(200);
	walkHorizontalAnimation.setFrameRate(200);


	playerName = std::to_string(rand() % 100000);

	// Timers start
	idleAnimationTimer.start();
	blinkSpeed.start();
	
	
	// Randomise the body remove when we have menu
	srand(time(NULL));
	this->body.eyeType = Body::EyeType(rand() % 13);
	this->body.earType = Body::EarType(rand() % 10);
	this->body.hairType = Body::HairType(rand() % 8);
	this->body.gender = Body::Gender(rand() % 2);
	this->PlayerClothes.body = Clothing::BodyWear(rand() % 4);
	this->PlayerClothes.leg = Clothing::LegWear(rand() % 4);



	// Render layer
	renderLayer = 3;
}



Player::~Player()
{
}

std::shared_ptr<Player> Player::getSharedPointer()
{
	if (playerPointer != nullptr)
	{
		return playerPointer;
	}
	else
	{
		playerPointer = std::make_shared<Player>(*this);
	}
	return playerPointer;
}

// Runs only when the player has been told to move
void Player::Move(Player::MovementDirection direction)
{

	this->direction = direction;
	switch(direction)
	{
	default:
		getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		break;
	case Player::MovementDirection::none:

		//setPosition(this->getX() + getVelocity().x, getY() + getVelocity().y);
		break;
	case Player::MovementDirection::right_down:
		getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), +getSpeed()), true);
		//getBody()->ApplyLinearImpulse(b2Vec2(+getSpeed(), +getSpeed()), b2Vec2(getX(), getY()), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x + getSpeed(), getBody()->GetTransform().p.y + getSpeed()), 0.0f);
		//setPosition(this->getX() + getVelocity().x, getY() + getVelocity().y);
		break;
	case Player::MovementDirection::right_up:
		getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), -getSpeed()), true);
		//getBody()->ApplyLinearImpulse(b2Vec2(+getSpeed(), -getSpeed()), b2Vec2(getX(), getY()), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x + getSpeed(), getBody()->GetTransform().p.y - getSpeed()), 0.0f);
		//setPosition(getX() + getVelocity().x, getY() - getVelocity().y);
		break;
	case Player::MovementDirection::left_down:
		getBody()->ApplyForceToCenter(b2Vec2(-getSpeed(), +getSpeed()), true);
		//getBody()->ApplyLinearImpulse(b2Vec2(-getSpeed(), +getSpeed()), b2Vec2(getX(), getY()), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x - getSpeed(), getBody()->GetTransform().p.y + getSpeed()), 0.0f);
		//setPosition(getX() - getVelocity().x, getY() + getVelocity().y);
		break;
	case Player::MovementDirection::left_up:
		getBody()->ApplyForceToCenter(b2Vec2(-getSpeed(), -getSpeed()), true);
		//getBody()->ApplyLinearImpulse(b2Vec2(-getSpeed(), -getSpeed()), b2Vec2(getX(), getY()), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x - getSpeed(), getBody()->GetTransform().p.y - getSpeed()), 0.0f);
		//setPosition(getX() - getVelocity().x, getY() - getVelocity().y);
		break;
	case Player::MovementDirection::up:
		getBody()->ApplyForceToCenter(b2Vec2(0.0f, -getSpeed()), true);
		//getBody()->ApplyLinearImpulse(b2Vec2(0.0f, -getSpeed()), b2Vec2(getX(), getY()), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x, getBody()->GetTransform().p.y - getSpeed()), 0.0f);
		//setPosition(getX(), getY() - getVelocity().x);
		break;
	case Player::MovementDirection::down:
		getBody()->ApplyForceToCenter(b2Vec2(0.0f, +getSpeed()), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x, getBody()->GetTransform().p.y + getSpeed()), 0.0f);
		//getBody()->ApplyLinearImpulse(b2Vec2(0.0f, +getSpeed()), b2Vec2(getX(), getY()), true);
		//setPosition(getX(), getY() + getVelocity().x);
		break;
	case Player::MovementDirection::left:
		getBody()->ApplyForceToCenter(b2Vec2(-getSpeed(), 0.0f), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x - getSpeed(), getBody()->GetTransform().p.y), 0.0f);
		//getBody()->ApplyLinearImpulse(b2Vec2(-getSpeed(), 0.0f), b2Vec2(getX(), getY()), true);
		//setPosition(getX() - getVelocity().x, getY());
		break;
	case Player::MovementDirection::right:
		//if (getBody()->GetLinearVelocity().x < maxSpeed)
		//getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), 0.0f), true);
		getBody()->ApplyForceToCenter(b2Vec2(+getSpeed(), 0.0f), true);
		//getBody()->ApplyLinearImpulse(b2Vec2(+getSpeed(), 0.0f), getBody()->GetPosition(), true);
		//getBody()->SetTransform(b2Vec2(getBody()->GetTransform().p.x + getSpeed(), getBody()->GetTransform().p.y), 0.0f);
		//setPosition(getX() + getVelocity().x, getY());
		break;
	}
}

void Player::Move(glm::vec2 newPos)
{
	//getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	//vec2 pos = getPosition();// { getBody()->GetPosition().x, getBody()->GetPosition().y };
	//float dist = GetDistance(pos, newPos);
	//
	//float lerp_x = getPosition().x + (newPos.x - getPosition().x) * 0.3f;
	//float lerp_y = getPosition().y + (newPos.y - getPosition().y) * 0.3f;
	//
	//lerp_x = 10.0f;
	//lerp_y = 10.0f;
	////if (dist > 200.0f)
	//{
	//	std::cout << "Distance to destination " << playerName << " is: " << dist <<  std::endl;
	//	//setPosition(newPos);
	//	//getBody()->SetTransform(b2Vec2(newPos.x, newPos.y), getBody()->GetAngle());
	//	getPosition();
	//}
	//if (dist > 1000.0f)
	//{
	//	if (newPos.x > pos.x)
	//		getBody()->ApplyForceToCenter(b2Vec2(+lerp_x, 0.0f), true);
	//	if (newPos.x < pos.x)
	//		getBody()->ApplyForceToCenter(b2Vec2(-lerp_x, 0.0f), true);
	//	if (newPos.y > pos.y)
	//		getBody()->ApplyForceToCenter(b2Vec2(0.0f, +lerp_y), true);
	//	if (newPos.y < pos.y)
	//		getBody()->ApplyForceToCenter(b2Vec2(0.0f, -lerp_y), true);
	//}
}

void Player::RenderPlayer(GL_Renderer& renderer, Camera& camera)
{
	
	//getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	this->setPosition({ this->getBody()->GetPosition().x *  physicsScaleUp,this->getBody()->GetPosition().y *  physicsScaleUp });
	//std::cout << "Player: " << this->getBody()->GetPosition().x * xMeters * 2000.0f << " _ " << this->getBody()->GetPosition().y * yMeters * 2000.0f << std::endl;
	//std::cout << "Player: " << this->getX() << " _ " << this->getY() << std::endl;
	getBody()->SetLinearDamping(1000.0f);
	//this->getBody()->SetTransform(b2Vec2(getBody()->GetPosition().x, getBody()->GetPosition().y), this->getRotation());
	if (isPlayerMoving())
	{
		walkHorizontalAnimation.OnAnimate();
		walkVerticalAnimation.OnAnimate();
		blink = false;
		playerAction = PlayerActions::none;
		fishingCast.setCurrentFrame(0);
		fishingReel.setCurrentFrame(0);
	}
	else
	{
		// Dont do idle when the player is perfoming an action
		if (playerAction == PlayerActions::none)
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
		
	}
	/// RENDER ROTATIONS ///
	//Walk Down (S)
	if (getTargetRotation() == 0 || getTargetRotation() == 360)
	{
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkVerticalAnimation.getCurrentFrame() + 20, false);
			//renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame(), renderOffset.x, renderOffset.y, pixelSize, size, false);
		}

		else
		{
			renderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame() + 20, false);
			//renderCharacterClothes(renderer, 0, renderOffset.x, renderOffset.y, pixelSize, size, false);
		}
	}


	// Walk Left (A)
	else if (getTargetRotation() == 90)
	{
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkHorizontalAnimation.getCurrentFrame(), true);
			//renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame(), 0, renderOffset.x, renderOffset.y, pixelSize, size, true);
		}
		else
		{
			renderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame(), true);
			//renderCharacterBody(renderer, 0, true);
			//renderCharacterClothes(renderer, 0, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, size, true);
		}

	}
	// Walk Right (D)
	else if (getTargetRotation() == 270)
	{
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkHorizontalAnimation.getCurrentFrame(), false);
			//renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame(), renderOffset.x, renderOffset.y, pixelSize, size, false);
		}

		else
		{
			renderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame(), false);

		}

	}
	// Walk Up (W)
	else if (getTargetRotation() == 180)
	{
		if (walkVerticalAnimation.getCurrentFrame() == 4)
			walkVerticalAnimation.setCurrentFrame(0);
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkVerticalAnimation.getCurrentFrame() + 10, false);
		}
		else
		{
			renderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame() + 10, false);

		}
	}
}

void Player::Render(GL_Renderer &renderer)
{
	RenderPlayer(renderer, renderer.camera);
}



void Player::renderCharacterBody(GL_Renderer& renderer, int index, bool flipSprite)
{
	
	AssignSprites(renderer, index, flipSprite);
	//playerShadow.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
	renderer.RenderSpriteLighting(this->nakedBody, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, bodyColour, { flipSprite, false });
	renderer.RenderSpriteLighting(this->hair, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->hairColour, { flipSprite, false });
	if(!blink)
		renderer.RenderSpriteLighting(this->eyes, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->eyeColour, { flipSprite, false });
	renderer.RenderSpriteLighting(this->ears, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->bodyColour, { flipSprite, false });
	if (bottom.Width > 0 && bottom.Height > 0)
		renderer.RenderSpriteLighting(this->bottom, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->bottomColour, { flipSprite, false });
	if(top.Width > 0 && top.Height > 0)
		renderer.RenderSpriteLighting(this->top, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->topColour, { flipSprite, false });

	playerLight.lightType = LightSource::LightType::playerAmbientLight;
	playerLight.setPosition(this->getPosition());
	playerLight.Render(renderer);
}


// Modify this data aswell as in gameSettings.getPlayerFromSave()
json Player::getPlayerJson()
{
	json playerData;
	playerData["PlayerData"]["name"] = playerName;
	playerData["PlayerData"]["rotation"] = getTargetRotation();
	playerData["PlayerData"]["X"] = getX();
	playerData["PlayerData"]["Y"] = getY();
	playerData["PlayerData"]["isMoving"] = isPlayerMoving();
	playerData["PlayerData"]["headWear"] = PlayerClothes.hat;
	playerData["PlayerData"]["hairColour"]["r"] = gethairColour().r;
	playerData["PlayerData"]["hairColour"]["g"] = gethairColour().g;
	playerData["PlayerData"]["hairColour"]["b"] = gethairColour().b;
	playerData["PlayerData"]["eyeColour"]["r"] = getEyeColour().r;
	playerData["PlayerData"]["eyeColour"]["g"] = getEyeColour().g;
	playerData["PlayerData"]["eyeColour"]["b"] = getEyeColour().b;
	playerData["PlayerData"]["bodyWear"] = PlayerClothes.body;
	playerData["PlayerData"]["upperClothesColour"]["r"] = getJacketColour().r;
	playerData["PlayerData"]["upperClothesColour"]["g"] = getJacketColour().g;
	playerData["PlayerData"]["upperClothesColour"]["b"] = getJacketColour().b;
	playerData["PlayerData"]["legWear"] = PlayerClothes.leg;
	playerData["PlayerData"]["legColour"]["r"] = getJeansColour().r;
	playerData["PlayerData"]["legColour"]["g"] = getJeansColour().g;
	playerData["PlayerData"]["legColour"]["b"] = getJeansColour().b;

	playerData["PlayerData"]["gender"] = body.gender;
	playerData["PlayerData"]["earType"] = body.earType;
	playerData["PlayerData"]["eyeType"] = body.eyeType;
	playerData["PlayerData"]["bodyColour"]["r"] = getBodyColour().r;
	playerData["PlayerData"]["bodyColour"]["g"] = getBodyColour().g;
	playerData["PlayerData"]["bodyColour"]["b"] = getBodyColour().b;

	return playerData;
}

void Player::collidedWith(CollisionIdentifier& objectIdentity)
{
	if (objectIdentity.entityType > 0)
	{
		std::cout << "Player Collided with: " << std::to_string(objectIdentity.entityType) << std::endl;
		if (objectIdentity.entityType == CollisionIdentifier::CollisionEntityTypes::projectile)
		{
			Projectile* projectile = static_cast<Projectile*>(objectIdentity.object);
			projectile->getSharedPointer()->AliveTime = 0;
		}
	}
}

void Player::Update()
{
}

Player Player::LoadFromJson(json playerData)
{
	// Player movement
	Player ExistingPlayer;
	int x = playerData.at("X").get<float>();
	int y = playerData.at("Y").get<float>();
	int rotation = playerData.at("rotation").get<int>();
	std::string name = playerData.at("name").get<std::string>();
	bool isMoving = playerData.at("isMoving").get<bool>();
	// Render layer
	ExistingPlayer.renderLayer = 3;
	// Player clothes

	// ints for converting the json enums
	int headWear;
	int bodyWear;
	int legWear;
	int EarType;
	int EyeType;
	int gender;

	// Check to see if the data is there
	if (playerData.count("headWear") > 0)
	{
		headWear = playerData.at("headWear").get<int>();
	}
	if (playerData.count("bodyWear") > 0)
	{
		bodyWear = playerData.at("bodyWear").get<int>();
	}
	if (playerData.count("bodyWear") > 0)
	{
		legWear = playerData.at("legWear").get<int>();
	}
	if (playerData.count("eyeType") > 0)
	{
		EyeType = playerData.at("eyeType").get<int>();
	}
	if (playerData.count("earType") > 0)
	{
		EarType = playerData.at("earType").get<int>();
	}
	if (playerData.count("gender") > 0)
	{
		gender = playerData.at("gender").get<int>();
	}
	json hairColour = playerData.at("hairColour");
	int hr = hairColour.at("r").get<int>();
	int hg = hairColour.at("g").get<int>();
	int hb = hairColour.at("b").get<int>();
	json eyeColour = playerData.at("eyeColour");
	int er = eyeColour.at("r").get<int>();
	int eg = eyeColour.at("g").get<int>();
	int eb = eyeColour.at("b").get<int>();
	json upperClothesColour = playerData.at("upperClothesColour");
	int jr = upperClothesColour.at("r").get<int>();
	int jg = upperClothesColour.at("g").get<int>();
	int jb = upperClothesColour.at("b").get<int>();
	json legsColour = playerData.at("legColour");
	int lr = legsColour.at("r").get<int>();
	int lg = legsColour.at("g").get<int>();
	int lb = legsColour.at("b").get<int>();
	json bodyColour = playerData.at("bodyColour");
	int br = bodyColour.at("r").get<int>();
	int bg = bodyColour.at("g").get<int>();
	int bb = bodyColour.at("b").get<int>();
	ExistingPlayer.setEyeColour(er, eg, eb);
	ExistingPlayer.setHairColour(hr, hg, hb);
	ExistingPlayer.setJacketColour(br, bg, bb);
	ExistingPlayer.setJeansColour(lr, lg, lb);
	ExistingPlayer.setBodyColour(br, bg, bb);

	ExistingPlayer.body.gender = (Player::Body::Gender)gender;
	ExistingPlayer.body.earType = (Player::Body::EarType)EarType;
	ExistingPlayer.body.eyeType = (Player::Body::EyeType)EyeType;
	ExistingPlayer.PlayerClothes.hat = (Player::Clothing::HeadWear)headWear;
	ExistingPlayer.PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
	ExistingPlayer.PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
	ExistingPlayer.setPlayerMoving(isMoving);
	return ExistingPlayer;
}

