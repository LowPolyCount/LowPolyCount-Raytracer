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
	void Init(const Vector3d& inPos, double inRadius);
	void Init(const DeserializeData& data);
	virtual bool IsCollision(const CollidableObject& rhs) const;


	inline const Vector3d& GetPosition() const { return position.GetPosition(); }
	inline double GetRadius() const{ return radius; }
	inline double GetRadiusSqr() const { return radiusSqr; }
protected:
	virtual bool IsCollisionPoint(const Point& rhs) const;
	virtual bool IsCollisionSphere(const Sphere& rhs) const;
private:
	Point		position;
	double		radius;
	double		radiusSqr;
};

