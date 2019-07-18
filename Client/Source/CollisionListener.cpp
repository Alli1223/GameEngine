#include "stdafx.h"
#include "CollisionListener.h"


CollisionListener::CollisionListener()
{
}


CollisionListener::~CollisionListener()
{
}

void CollisionListener::BeginContact(b2Contact* contact) {
	
	//Get two collision objects
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void *bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	// A collided with B
	if (bodyUserDataA)
	{
		CollisionIdentifier* firstObject = static_cast<CollisionIdentifier*>(bodyUserDataA);
		if (firstObject->entityType > 0)
		{
			if (firstObject->entityType == CollisionIdentifier::CollisionEntityTypes::player)
			{
				Player* player = static_cast<Player*>(firstObject->object);
		
				player->getSharedPointer()->setHairColour({ rand() % 100, rand() % 100, rand() % 100 });
		
				// second object
				if (bodyUserDataB)
				{
					CollisionIdentifier* secondObject = static_cast<CollisionIdentifier*>(bodyUserDataB);
					player->collidedWith(*secondObject);
				}
				else
				{
		
				}
			}
		}
	}

	// B collided with A
	//if (bodyUserDataB)
	//{
	//	CollisionIdentifier* firstObject = static_cast<CollisionIdentifier*>(bodyUserDataB);
	//	if (firstObject->entityType > 0)
	//	{
	//		if (firstObject->entityType == CollisionIdentifier::CollisionEntityTypes::player)
	//		{
	//			Player* player = static_cast<Player*>(firstObject->object);
	//
	//			player->getSharedPointer()->setHairColour({ rand() % 100, rand() % 100, rand() % 100 });
	//
	//			// second object
	//			if (bodyUserDataA)
	//			{
	//				CollisionIdentifier* secondObject = static_cast<CollisionIdentifier*>(bodyUserDataA);
	//				player->collidedWith(*secondObject);
	//			}
	//			else
	//			{
	//
	//			}
	//		}
	//	}
	//
	//}

}

void CollisionListener::EndContact(b2Contact* contact) {

	////check if fixture A was a ball
	//void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	//if (bodyUserData)
	//	static_cast<GameObject*>(bodyUserData)->endContact();
	//
	////check if fixture B was a ball
	//bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	//if (bodyUserData)
	//	static_cast<GameObject*>(bodyUserData)->endContact();

}