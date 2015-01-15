#pragma once
#include "Vector3d.h"
#include "CollidableObject.h"

struct DeserializeData;
class Plane : public CollidableObject
{
public:
	Plane();
	~Plane();
	void Init(const DeserializeData& data);
	void Init(const Vector3d& upperLeft, const Vector3d& lowerRight);
	inline const Vector3d& GetUpperLeft() const { return m_upperLeft; }
	inline const Vector3d& GetLowerRight() const { return m_lowerRight; }
	double GetWidth() const;
	double GetHeight() const;
private:
	Vector3d	m_upperLeft;
	Vector3d	m_lowerRight;
};
