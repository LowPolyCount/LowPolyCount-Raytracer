#pragma once
#include "Vector3d.h"
#include "CollidableObject.h"
#include "Point.h"

struct DeserializeData;
class Ray : public CollidableObject
{
public:
	Ray();
	Ray(const Vector3d& pos, const Vector3d& dir);
	virtual ~Ray();
	virtual bool IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const;

	void Init(const DeserializeData& data);
	void Init(const Vector3d& pos, const Vector3d& dir);
	bool operator ==(const Ray& rhs) const;

	inline const Vector3d& GetPosition() const { return m_position.GetPosition(); }
	inline const Vector3d& GetDirection() const { return m_direction; }
	inline void SetPosition(const Vector3d& pos) { m_position = pos; }
	inline void SetDirection(const Vector3d& dir) { m_direction = dir; }

private:
	bool IsCollisionPoint(const Point& rhs, Vector3d& pointOfIntersect) const;
	bool IsCollisionSphere(const Sphere& rhs, Vector3d& pointOfIntersect) const;
	bool IsCollisionRay(const Ray& rhs, Vector3d& pointOfIntersect) const;

	Point m_position;
	Vector3d m_direction;
};

