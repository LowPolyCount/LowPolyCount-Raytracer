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

RGBA CollidableObject::GetLastMaterialHit() const
{ 
	assert(false);
	return COLOR_WHITE; 
}