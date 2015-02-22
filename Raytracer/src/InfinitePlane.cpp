#include "stdafx.h"
#include <gtest\gtest.h>
#include <assert.h>
#include "InfinitePlane.h"
#include "Ray.h"
#include "DeserializeData.h"

using namespace std;

InfinitePlane::InfinitePlane()
:CollidableObject(CT_InfinitePlane)
{
}

InfinitePlane::InfinitePlane(const Vector3d& pos, const Vector3d& dir)
: CollidableObject(CT_InfinitePlane)
{
	Init(pos, dir);
}

InfinitePlane::~InfinitePlane()
{

}

bool InfinitePlane::IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const
{
	// TODO: Handle this in a more generic way
	switch (rhs.GetType())
	{
	case WorldType::CT_Ray:
		return static_cast<const Ray&>(rhs).IsCollision(*this, pointOfIntersect);
	default:
		cout << "DEFAULT IsCollision" << endl;
		assert(true);
		break;
	}

	return false;
}

void InfinitePlane::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapVector.at(DeserializeData::DIRECTION));

	// TODO: Move conversion to a utility function.
	Vector3d material = data.m_mapVector.at(DeserializeData::MATERIAL);
	m_lastMaterialHit = static_cast<int>(material.x) + (static_cast<int>(material.y) << 8) + (static_cast<int>(material.z) << 16);
}

RGBA InfinitePlane::GetLastMaterialHit() const
{
	return m_lastMaterialHit;
}


void InfinitePlane::Init(const Vector3d& pos, const Vector3d& dir)
{
	m_position = pos;
	m_direction = dir.Normalize();
}

bool InfinitePlane::operator == (const InfinitePlane& rhs) const
{
	return m_position == rhs.GetPosition() && m_direction == rhs.GetDirection();
}

/*TEST(InfinitePlaneCollision, InfinitePlane)
{

}*/
