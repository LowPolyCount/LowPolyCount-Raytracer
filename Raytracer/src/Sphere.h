#pragma once
#include "CollidableObject.h"
#include "Vector3d.h"
#include "Point.h"
#include "Material.h"

/**
Defines your basic sphere
*/
struct DeseralizeData;
class Sphere : public CollidableObject
{
public:
	Sphere();
	Sphere(double inRadius);
	Sphere(const Vector3d& inPos, double inRadius);
	~Sphere();
	virtual void Init(const Vector3d& inPos, double inRadius);
	virtual void Init(const DeserializeData& data);
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;

	inline const Vector3d& GetPosition() const { return m_position.GetPosition(); }
	inline double GetRadius() const{ return m_radius; }
	inline double GetRadiusSqr() const { return m_radiusSqr; }
private:
	Point		m_position;
	double		m_radius;
	double		m_radiusSqr;

	//@todo: We don't technically have a normal, but using this removes "warning C4172: returning address of local variable or temporary" when calling getNormal
	// may want to consider having GetNormal() return a copy instead of a reference
	//@todo: this is mutable just until GetNormal() returns a copy
	mutable Vector3d	m_normal;
};

