#pragma once

#include "CollidableObject.h"
#include "Vector3d.h"

class Sphere;
struct DeserializeData;
class Point : public CollidableObject
{
public:
	Point();
	Point(const Vector3d& pos);
	virtual ~Point();
	virtual bool IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect);

	void Init(const Vector3d& pos);
	void Init(const DeserializeData& data);
	virtual bool IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const;
	inline void SetPosition(const Vector3d& pos){ m_position = pos; }
	inline const Vector3d& GetPosition() const { return m_position; }
	inline bool Point::operator == (const Point& rhs) const{ return m_position == rhs.GetPosition(); }

protected:
	bool IsCollisionPoint(const Point& rhs, Vector3d& pointOfIntersect);
	bool IsCollisionSphere(const Sphere& rhs, Vector3d& pointOfIntersect);

private:
	Vector3d m_position;
};

