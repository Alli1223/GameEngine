#include "stdafx.h"
#include "GameObject.h"



//Constructors
GameObject::GameObject()
	: position(0, 0), size(10, 10), velocity(0.0f), colour(0.0f), rotation(0.0f), Sprite() { }
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: position(pos), size(size), velocity(velocity), colour(color), rotation(0.0f), Sprite(sprite) { }

GameObject::~GameObject()
{
}

void GameObject::InitPhysics(b2World* physicsWorld, b2BodyType type, float density, float friction)
{

	if (!hasPhysics)
	{
		b2BodyDef rigidbody;
		rigidbody.type = type;
		rigidbody.position.Set(this->position.x * physicsScaleDown, this->position.y * physicsScaleDown);
		rigidBody = physicsWorld->CreateBody(&rigidbody);
		
		b2PolygonShape box;
		xMeters = physicsScaleDown * (size.x / 2.0f);
		yMeters = physicsScaleDown * (size.y / 2.0f);

		//physicsScaleUp = 50.0f;
		box.SetAsBox(xMeters, yMeters);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.userData = this;

		// Empty identifier
		CollisionIdentifier objectIdnetifier(CollisionIdentifier::CollisionEntityTypes::empty);
		fixtureDef.userData = &objectIdnetifier;
		rigidBody->SetUserData(&objectIdnetifier);

		//b2ContactListener contact;
		//contactListener = &contact;
		//physicsWorld->SetContactListener(&contact);


		fixture = rigidBody->CreateFixture(&fixtureDef);
		hasPhysics = true;
	}
}

void GameObject::InitPhysics(b2World * physicsWorld, CollisionIdentifier& objectIdnetifier, b2BodyType type, float density, float friction)
{
	// If it already has physics, remove it
	if (!hasPhysics)
	{
		b2BodyDef rigidbody;
		rigidbody.type = type;
		rigidbody.position.Set(this->position.x * physicsScaleDown, this->position.y * physicsScaleDown);
		rigidBody = physicsWorld->CreateBody(&rigidbody);

		b2PolygonShape box;
		xMeters = physicsScaleDown * (size.x / 2.0f);
		yMeters = physicsScaleDown * (size.y / 2.0f);

		//physicsScaleUp = 50.0f;
		box.SetAsBox(xMeters, yMeters);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.userData = &objectIdnetifier;

		rigidBody->SetUserData(&objectIdnetifier);

		//b2ContactListener contact;
		//objectContactListener = &contact;
		//physicsWorld->SetContactListener(objectContactListener);

		fixture = rigidBody->CreateFixture(&fixtureDef);
		hasPhysics = true;
	}
}

void GameObject::InitSprite()
{
	this->Sprite = ResourceManager::LoadTexture(spritePath);
	this->NormalMap = ResourceManager::LoadTexture(spritePath_normal);
	initalised = true;
}



void GameObject::Render(GL_Renderer &renderer)
{
	if(hasPhysics)
		this->setPosition({ this->getBody()->GetPosition().x * physicsScaleUp,this->getBody()->GetPosition().y *  physicsScaleUp });
	renderer.RenderSpriteLighting(this->Sprite, this->NormalMap, this->position, this->size, this->rotation,this->transparency,this->renderLayer, this->colour, flipSprite);
}



bool GameObject::collidesWith(GameObject object)
{
	int top1, top2, left1, left2, right1, right2, bottom1, bottom2;

	// This object
	top1 = this->getY() - (this->getSize().y / 2);
	left1 = this->getX() - (this->getSize().x / 2);
	right1 = this->getX() + (this->getSize().x / 2);
	bottom1 = this->getY() + (this->getSize().y / 2);


	// That object
	top2 = object.getY() - (object.getSize().y / 2);
	left2 = object.getX() - (object.getSize().x / 2);
	right2 = object.getX() + (object.getSize().x / 2);
	bottom2 = object.getY() + (object.getSize().y / 2);


	return !(left2 > right1 ||	right2 < left1 ||	top2 > bottom1 ||	bottom2 < top1);

	//if (SDL_HasIntersection(&this->getTexture().getRect(), &object.getTexture().getRect()) == SDL_TRUE)
	//{
	//	return true;
	//}
	//else
	//	return false;

}

void GameObject::collidedWith(CollisionIdentifier & objectIdentity)
{
}
