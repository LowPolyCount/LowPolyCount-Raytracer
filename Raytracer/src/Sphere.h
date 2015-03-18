#pragma once
#include "CollidableObject.h"
#include "Vector3d.h"
#include "Point.h"

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
	virtual RGBA GetLastMaterialHit() const;


	inline const Vector3d& GetPosition() const { return m_position.GetPosition(); }
	inline double GetRadius() const{ return m_radius; }
	inline double GetRadiusSqr() const { return m_radiusSqr; }
private:
	Point		m_position;
	RGBA		m_lastMaterialHit;
	double		m_radius;
	double		m_radiusSqr;
};

