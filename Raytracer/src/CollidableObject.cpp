#include "stdafx.h"
#include <iostream>
#include "CollidableObject.h"

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

RGBA CollidableObject::GetLastMaterialHit() const
{ 
	return COLOR_WHITE; 
}
