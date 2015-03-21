#include "stdafx.h"
#include <iostream>
#include "CollidableObject.h"

using namespace std;

CollidableObject::CollidableObject(ObjectType inType) 
:Object(inType)
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