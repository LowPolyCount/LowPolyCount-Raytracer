#pragma once

#include "CollidableObject.h"
#include "Vector3d.h"

class Sphere;
struct DeserializeData;

/*
Defines a point that exists in space. Used just for theoretical purposes and unit tests.
*/
class Point : public CollidableObject
{
public:
	Point();
	Point(const Vector3d& pos);
	virtual ~Point();
	void Init(const Vector3d& pos);
	virtual void Init(const DeserializeData& data);
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;
	inline void SetPosition(const Vector3d& pos){ m_position = pos; }
	virtual const Vector3d& GetPosition() const { return m_position; }
	inline bool Point::operator == (const Point& rhs) const{ return m_position == rhs.GetPosition(); }
private:
	Vector3d m_position;
};

