#pragma once
#include "CollidableObject.h"
#include "Material.h"

class Light : public CollidableObject
{
public:
	Light();
	virtual ~Light();
	virtual void Light::Init(const DeserializeData& data);
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;
};

