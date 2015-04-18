#pragma once
#include "Vector3d.h"
#include "CollidableObject.h"
#include "Point.h"
#include "InfinitePlane.h"

struct DeserializeData;
class Ray : public CollidableObject
{
public:
	Ray();
	Ray(const Vector3d& pos, const Vector3d& dir);
	virtual ~Ray();

	void Init(const DeserializeData& data);
	void Init(const Vector3d& pos, const Vector3d& dir);
	bool operator ==(const Ray& rhs) const;

	inline const Vector3d& GetPosition() const { return m_position.GetPosition(); }
	inline const Vector3d& GetDirection() const { return m_direction; }
	inline void SetPosition(const Vector3d& pos) { m_position = pos; }
	inline void SetDirection(const Vector3d& dir) { m_direction = dir; }
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;
	void MoveByDelta(double);

private:
	Point m_position;	// @todo: remove Point and just use a vector3d
	Vector3d m_direction;
};

