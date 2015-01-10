#include "stdafx.h"
#include "CollidableObject.h"
#include <iostream>

using namespace std;

CollidableObject::CollidableObject(WorldType inType) 
:WorldObject(inType)
{
}

CollidableObject::~CollidableObject()
{
}

bool CollidableObject::IsCollision(const CollidableObject& rhs) const
{
	cout << "Calling IsCollision in ICollidable!" << endl;
	return false;
}
