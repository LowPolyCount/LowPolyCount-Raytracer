#pragma once

#include "WorldObject.h"
#include "RaytracerTypes.h"
#include "Vector3d.h"

class CollidableObject: public WorldObject
{
public:
	CollidableObject(WorldType inType);
	virtual ~CollidableObject();
	virtual RGBA GetLastMaterialHit() const;
};

