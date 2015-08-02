#pragma once

#include "Object.h"
#include "RaytracerTypes.h"
#include "Vector3d.h"
#include "Material.h"
#include <vector>
#include <memory>

class Ray;
class Light;

class CollidableObject: public Object
{
public:
	CollidableObject(ObjectType inType);
	virtual ~CollidableObject();
	virtual const Vector3d& GetPosition() const{ return m_position; }
	virtual const Material& GetMaterial() const;
	virtual RGBA GetLastMaterialHit() const { return m_material.GetColor().ToRGBA(); }
	//@ TODO: Find a way to extract out the getNormal call since not all objects (IE Lights) have one.
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const = 0;
	virtual Vector3d CalculateMaterialHit(const Ray& testRay, const Vector3d& intersectPoint, const std::vector<const std::shared_ptr<Light>>& hitLights) const;
protected:
	Material m_material;
	Vector3d m_position;
};

