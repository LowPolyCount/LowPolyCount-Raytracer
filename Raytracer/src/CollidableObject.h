#pragma once

#include "Object.h"
#include "RaytracerTypes.h"
#include "Vector3d.h"

class CollidableObject: public Object
{
public:
	CollidableObject(ObjectType inType);
	virtual ~CollidableObject();
	virtual RGBA GetLastMaterialHit() const;
	virtual const Vector3d& GetPosition() const{ return m_position; }
protected:
	Vector3d m_position;
};

