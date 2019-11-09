#include "stdafx.h"
#include "Character.h"



Character::Character()
{
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
}


Character::~Character()
{
}


void RenderCharacter()
{

}

void Character::Move(int newX, int newY)
{
	
}

void Character::RotateCharacter(GL_Renderer& renderer)
{
	// Walk down
	if (getTargetRotation() == -90)
	{
		if (isPlayerMoving())
		{
			RenderCharacterBody(renderer, walkVerticalAnimation.getCurrentFrame() + 20, false);
			//renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame(), renderOffset.x, renderOffset.y, pixelSize, size, false);
		}

		else
		{
			RenderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame() + 20, false);
			//renderCharacterClothes(renderer, 0, renderOffset.x, renderOffset.y, pixelSize, size, false);
		}
	}


	// Walk Left (A)
	else if (getTargetRotation() == 0)
	{
		if (isPlayerMoving())
		{
			RenderCharacterBody(renderer, walkHorizontalAnimation.getCurrentFrame(), true);
			//renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame(), 0, renderOffset.x, renderOffset.y, pixelSize, size, true);
		}
		else
		{
			RenderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame(), true);
			//renderCharacterBody(renderer, 0, true);
			//renderCharacterClothes(renderer, 0, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, size, true);
		}

	}
	// Walk Right (D)
	
	else if (getTargetRotation() == 180 || getTargetRotation() == -180)
	{
		if (isPlayerMoving())
		{
			RenderCharacterBody(renderer, walkHorizontalAnimation.getCurrentFrame(), false);
			//renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame(), renderOffset.x, renderOffset.y, pixelSize, size, false);
		}

		else
		{
			RenderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame(), false);

		}

	}
	// Walk Up (W)
	else if (getTargetRotation() == 90)
	{
		if (walkVerticalAnimation.getCurrentFrame() == 4)
			walkVerticalAnimation.setCurrentFrame(0);
		if (isPlayerMoving())
		{
			RenderCharacterBody(renderer, walkVerticalAnimation.getCurrentFrame() + 10, false);
		}
		else
		{
			RenderCharacterBody(renderer, legFlipIdleAnimation.getCurrentFrame() + 10, false);

		}

	}
}

void Character::RenderCharacterBody(GL_Renderer& renderer, int index, bool flipSprite)
{

	AssignSprites(renderer, index, flipSprite);
	//playerShadow.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
	renderer.RenderSpriteLighting(this->nakedBody, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, bodyColour, { flipSprite, false });
	renderer.RenderSpriteLighting(this->hair, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->hairColour, { flipSprite, false });
	if (!blink)
		renderer.RenderSpriteLighting(this->eyes, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->eyeColour, { flipSprite, false });
	renderer.RenderSpriteLighting(this->ears, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->bodyColour, { flipSprite, false });
	if (bottom.Width > 0 && bottom.Height > 0)
		renderer.RenderSpriteLighting(this->bottom, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->bottomColour, { flipSprite, false });
	if (top.Width > 0 && top.Height > 0)
		renderer.RenderSpriteLighting(this->top, this->NormalMap, this->position, this->size, this->rotation, this->transparency, this->renderLayer, this->topColour, { flipSprite, false });

	playerLight.lightType = LightSource::LightType::playerAmbientLight;
	playerLight.setPosition(this->getPosition());
	playerLight.Render(renderer);
}

void Character::AssignSprites(GL_Renderer& renderer, int index, bool flipSprite)
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

	switch (PlayerClothes.body)
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
	switch (PlayerClothes.leg)
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

	// Load animations
	/// Load Fising cast
	if (fishingCast.Sprites.size() == 0)
	{
		if (body.gender == Character::Body::Gender::male)
			for (int i = 0; i < fishingCast.maxFrames; i++)
				fishingCast.Sprites.push_back(ResourceManager::GetAtlasTexture("maleFishing", i));

		if (body.gender == Character::Body::Gender::female)
			for (int i = 0; i < fishingCast.maxFrames; i++)
				fishingCast.Sprites.push_back(ResourceManager::GetAtlasTexture("femaleFishing", i));
	}

	// Set Animations
	//switch (playerAction)
	//{
	//default:
	//	break;
	//case PlayerActions::fishingCasting:
	//
	//	fishingCast.OnAnimate();
	//	nakedBody = fishingCast.Sprites[fishingCast.getCurrentFrame()];
	//	break;
	//case PlayerActions::fishingReeling:
	//	fishingReel.OnAnimate();
	//	if (!fishingReel.getCurrentFrame() == fishingReel.maxFrames)
	//		nakedBody = fishingReel.Sprites[fishingReel.getCurrentFrame()];
	//	break;
	//}

}
