#pragma once

#include "WorldObject.h"
#include "RaytracerTypes.h"
#include "Vector3d.h"

class CollidableObject: public WorldObject
{
public:
	CollidableObject(WorldType inType);
	virtual ~CollidableObject();
	virtual bool IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const =0;
	virtual RGBA GetLastMaterialHit() const;
};

