#pragma once
#include "CollidableObject.h"
#include "InfinitePlane.h"
#include "Material.h"

/*
Defines a triangle
*/
class Triangle :
	public CollidableObject
{
public:
	Triangle();
	virtual ~Triangle();
	virtual void Init(const DeserializeData& data);
	void Init(const Vector3d& inPoint1, const Vector3d& inPoint2, const Vector3d& inPoint3);
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;
	inline const InfinitePlane& GetPlane() const { return m_plane; }
	inline const Vector3d& GetPoint1() const { return m_point1; }
	inline const Vector3d& GetPoint2() const { return m_point2; }
	inline const Vector3d& GetPoint3() const { return m_point3; }
private:
	Vector3d		m_point1;
	Vector3d		m_point2;
	Vector3d		m_point3;
	InfinitePlane	m_plane;
};

