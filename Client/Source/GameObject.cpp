#include "stdafx.h"
#include "GameObject.h"



//Constructors
GameObject::GameObject()
	: position(0, 0), size(10, 10), velocity(0.0f), colour(0.0f), rotation(0.0f), Sprite(){ }
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: position(pos), size(size), velocity(velocity), colour(color), rotation(0.0f), Sprite(sprite) { }

GameObject::~GameObject()
{
	// Remove physics from world
	if (rigidBody != nullptr)
	{
		//getBody()->GetWorld()->DestroyBody(rigidBody);
	}
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
		//density *= 4.0;
		//friction *= 4.0;

		//physicsScaleUp = 50.0f;
		box.SetAsBox(xMeters, yMeters);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &box;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		//fixtureDef.userData = this;

		// Empty identifier
		CollisionIdentifier objectIdnetifier(CollisionIdentifier::CollisionEntityTypes::empty);
		//fixtureDef.userData = &objectIdnetifier;
		if(rigidBody != nullptr)
			rigidBody->SetUserData(&objectIdnetifier);

		//b2ContactListener contact;
		//contactListener = &contact;
		//physicsWorld->SetContactListener(&contact);

		if (rigidBody != nullptr)
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

void GameObject::RenderAnimation(Animation& anim, std::string atlasName)
{
	anim.OnAnimate();
	int test = 2;
	this->Sprite = ResourceManager::GetAtlasTexture(atlasName, anim.getCurrentFrame());

}

json GameObject::GetJson()
{
	json empty;
	return empty;
}

float GameObject::GetDistance(vec2 pointA, vec2 pointB)
{
	float dx = pointA.x - pointB.x;
	float dy = pointA.y - pointB.y;
	//pythagoras(sp)
	float dist = 0.0;

	dist = pow(dx, 2) + pow(dy, 2);
	dist = sqrt(dist);

	return dist;
}



glm::vec2 GameObject::setBodyPosition(glm::vec2 newPosition)
{
	if (getBody() != nullptr)
	{
		getBody()->SetTransform({ newPosition.x * physicsScaleDown, newPosition.y * physicsScaleDown }, getRotation());
	}
	return glm::vec2();
}

glm::vec2 GameObject::getPosition()
{
	return position;
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
}

NetworkObject::NetworkObject()
{
}

NetworkObject::NetworkObject(int ID)
{
}

void NetworkObject::NetworkUpdate(json data)
{
	std::string type = data.at("Type").get<std::string>();
	if (type == "Projectile")
	{

	}

	// Player movement
	float x = data.at("X").get<float>();
	float y = data.at("Y").get<float>();
	int rotation = data.at("rotation").get<int>();
	bool moving = data.at("isMoving").get<bool>();
	//int health = data.at("health").get<int>();
	lastKnownPos = { x,y };
	//setPosition(x, y);
	setRotation(rotation);
}
