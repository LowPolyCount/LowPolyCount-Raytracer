#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>
#include <math.h>
#include "Sphere.h"
#include "DeserializeData.h"
#include "Ray.h"

using namespace std;

Sphere::Sphere()
: CollidableObject(WorldType::CT_Sphere)
, m_position()
, m_radius(0)
, m_radiusSqr(0)
{
}

Sphere::Sphere(const Vector3d& inPos, double inRadius)
: CollidableObject(WorldType::CT_Sphere)
, m_position()
, m_radius(0)
, m_radiusSqr(0)
{
	Init(inPos, inRadius);
}

Sphere::~Sphere(){}

void Sphere::Init(const Vector3d& inPos, double inRadius)
{
	m_position.Init(inPos);

	m_radius = inRadius;
	m_radiusSqr = (inRadius*inRadius);
}

void Sphere::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapDouble.at(DeserializeData::RADIUS));
	Vector3d material = data.m_mapVector.at(DeserializeData::MATERIAL);
	//m_materials = data.m_mapVector.at(DeserializeData::MATERIAL);
	m_lastMaterialHit = static_cast<int>(material.x) + (static_cast<int>(material.y) << 8) + (static_cast<int>(material.z) << 16);
}

RGBA Sphere::GetLastMaterialHit() const
{
	return m_lastMaterialHit;
}

bool Sphere::IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const
{
	switch (rhs.GetType())
	{
	case WorldType::CT_Point:
		return IsCollisionPoint(static_cast<const Point&>(rhs));
	case WorldType::CT_Sphere:
		return IsCollisionSphere(static_cast<const Sphere&>(rhs));
	case WorldType::CT_Ray:
		return static_cast<const Ray&>(rhs).IsCollision(*this, pointOfIntersect);
	default:
		cout << "DEFAULT IsCollision" << endl;
		break;
	}

	return false;
}

bool Sphere::IsCollisionPoint(const Point& rhs) const
{
	const double rhsLength = std::abs((m_position.GetPosition() - rhs.GetPosition()).lengthSqr());
	return (rhsLength <= m_radiusSqr);
}

bool Sphere::IsCollisionSphere(const Sphere& rhs) const
{
	const double rhsLength = std::abs((m_position.GetPosition() - rhs.GetPosition()).lengthSqr());
	return (rhsLength <= (m_radiusSqr+rhs.GetRadiusSqr()));
}

TEST(PointCollision, Sphere)
{
	Point test1(Vector3d(1,1,1));
	Point test2(Vector3d(5, 5, 5));
	Sphere sphr(Vector3d(.5, .5, .5), 1);

	EXPECT_TRUE(sphr.IsCollision(test1, Vector3d()));
	EXPECT_FALSE(sphr.IsCollision(test2, Vector3d()));
}

TEST(SphereCollision, Sphere)
{
	Sphere test1(Vector3d(1, 1, 1), 1);
	Sphere test2(Vector3d(5, 5, 5), 10);
	Sphere test3(Vector3d(5, 5, 5), 1);
	Sphere sphr(Vector3d(.5, .5, .5), 1);

	EXPECT_TRUE(sphr.IsCollision(test1, Vector3d()));
	EXPECT_TRUE(sphr.IsCollision(test2, Vector3d()));
	EXPECT_FALSE(sphr.IsCollision(test3, Vector3d()));
}

TEST(RayCollision, Sphere)
{
}