#pragma once
#include "Vector3d.h"
#include "CollidableObject.h"

// TOOD: Rename to something more appropriate
/*
This Plane class is currently used only by the camera.  For other classes, use InfinitePlane class
@todo: Remove camera's use of this class and instead use InfinitePlane
*/
struct DeserializeData;
class Plane : public CollidableObject
{
public:
	Plane();
	virtual ~Plane();
	virtual bool IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const;

	virtual void Init(const DeserializeData& data);
	void Init(const Vector3d& upperLeft, const Vector3d& lowerRight);
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;
	inline const Vector3d& GetUpperLeft() const { return m_upperLeft; }
	inline const Vector3d& GetLowerRight() const { return m_lowerRight; }
	double GetWidth() const;
	double GetHeight() const;

private:
	Vector3d	m_upperLeft;
	Vector3d	m_lowerRight;
	//@todo: We don't technically have a normal, but using this removes "warning C4172: returning address of local variable or temporary" when calling getNormal
	Vector3d	m_normal;		
};

