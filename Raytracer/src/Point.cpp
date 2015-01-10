#include "stdafx.h"
#include "gtest\gtest.h"
#include "Point.h"
#include "Sphere.h"
#include "DeserializeData.h"


Point::Point()
: CollidableObject(WorldType::CT_Point)
, m_position()
{}

Point::Point(const Vector3d& pos)
: CollidableObject(WorldType::CT_Point)
, m_position()
{
	Init(pos);
}

Point::~Point() {}

bool Point::IsCollision(const CollidableObject& rhs) const
{
	switch (rhs.GetType())
	{
	case WorldType::CT_Point:
		return IsCollisionPoint(static_cast<const Point&>(rhs));
	case WorldType::CT_Sphere:
		return IsCollisionSphere(static_cast<const Sphere&>(rhs));
	default:
		break;
	}

	return false;
}

void Point::Init(const Vector3d& pos)
{
	m_position = pos;
}

void Point::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION));
}

bool Point::IsCollisionPoint(const Point& rhs) const
{
	return (*this) == rhs;
}

bool Point::IsCollisionSphere(const Sphere& rhs) const
{
	return rhs.IsCollision(*this);
}

TEST(PointCollision, Point)
{
	Point test1(Vector3d(1, 1, 1));
	Point test2(Vector3d(5, 5, 5));
	Sphere sphr(Vector3d(.5, .5, .5), 1);

	EXPECT_TRUE(test1.IsCollision(sphr));
	EXPECT_FALSE(test2.IsCollision(sphr));
}

TEST(SphereCollision, Point)
{
	Sphere test1(Vector3d(1, 1, 1), 1);
	Sphere test2(Vector3d(5, 5, 5), 10);
	Sphere test3(Vector3d(5, 5, 5), 1);
	Sphere sphr(Vector3d(.5, .5, .5), 1);

	EXPECT_TRUE(test1.IsCollision(sphr));
	EXPECT_TRUE(test2.IsCollision(sphr));
	EXPECT_FALSE(test3.IsCollision(sphr));
}

