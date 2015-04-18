#pragma once
#include "Vector3d.h"
#include "CollidableObject.h"
#include "Point.h"
#include "Material.h"

/**
Defines a Plane that runs into infinity
*/
//@todo: Can eventually merge this into the regular plane object
struct DeserializeData;
class InfinitePlane : public CollidableObject
{
public:
	InfinitePlane();
	InfinitePlane(const Vector3d& pos, const Vector3d& dir);
	virtual ~InfinitePlane();

	void Init(const DeserializeData& data);
	void Init(const Vector3d& pos, const Vector3d& dir);
	virtual const Vector3d& GetNormal(const Vector3d& intersectPoint) const;

	//@todo: Add Move operation
	bool operator ==(const InfinitePlane& rhs) const;
	

	inline const Vector3d& GetPosition() const { return m_position.GetPosition(); }
	inline const Vector3d& GetDirection() const { return m_direction; }
	inline void SetPosition(const Vector3d& pos) { m_position = pos; }
	inline void SetDirection(const Vector3d& dir) { m_direction = dir; }

private:
	Point m_position;
	Vector3d m_direction;
};