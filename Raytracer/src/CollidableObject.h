#pragma once

#include "WorldObject.h"
#include "RaytracerTypes.h"

class CollidableObject: public WorldObject
{
public:
	CollidableObject(WorldType inType);
	virtual ~CollidableObject();
	virtual bool IsCollision(const CollidableObject& rhs) const;
	virtual RGBA GetLastMaterialHit() const;
};

