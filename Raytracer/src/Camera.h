#pragma once
#include "Vector3d.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"

class Camera: public Object
{
public:
	Camera();
	virtual ~Camera();
	void Init(const DeserializeData& data);
	void Init(const Vector3d& inPos, const Vector3d& inDir, const Plane& inNearPlane);
	Ray CreateRay(int column, int row, int maxColumn, int maxRow);

	inline const Vector3d& GetPosition() const { return m_position; }
	inline const Vector3d& GetDirection() const { return m_direction; }

	inline const Plane& GetNearPlane() const { return m_nearPlane; }
	inline const Plane& GetFarPlane() const { return m_farPlane; }

	
private:
	Vector3d	m_position;
	Vector3d	m_direction;
	Plane		m_nearPlane;
	//@TODO Add Far Plane
	Plane		m_farPlane;
};

