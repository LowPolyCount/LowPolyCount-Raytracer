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

/*bool CollidableObject::IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect)
{
	assert(false);
	return false;
}*/

RGBA CollidableObject::GetLastMaterialHit() const
{ 
	assert(false);
	return COLOR_WHITE; 
}

Vector3d CollidableObject::GetLastRayHit() const
{
	assert(false);
	return Vector3d();
}