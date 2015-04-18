#include "stdafx.h"
#include <iostream>
#include "CollidableObject.h"
#include "Ray.h"
#include "Light.h"
#include "WorldManager.h"

using namespace std;

CollidableObject::CollidableObject(ObjectType inType) 
:Object(inType)
{
}

CollidableObject::~CollidableObject()
{
}

const Material& CollidableObject::GetMaterial() const
{
	return m_material;
}


Vector3d CollidableObject::CalculateMaterialHit(const Ray& testRay, const Vector3d& intersectPoint, const std::vector<const Light*>& hitLights) const
{
	return m_material.CalculateMaterialHit(testRay, intersectPoint, GetNormal(intersectPoint), hitLights);
}