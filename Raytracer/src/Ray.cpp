#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>
#include <math.h>
#include "Ray.h"
#include "Sphere.h"
#include "Point.h"
#include "DeserializeData.h"


using namespace std;

Ray::Ray()
:CollidableObject(CT_Ray)
{
}

Ray::Ray(const Vector3d& pos, const Vector3d& dir)
: CollidableObject(CT_Ray)
{
	Init(pos, dir);
}

Ray::~Ray()
{
}

bool Ray::operator ==(const Ray& rhs) const
{
	return rhs.GetPosition() == this->GetPosition() && rhs.GetDirection() == this->GetDirection();
}

void Ray::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapVector.at(DeserializeData::DIRECTION));
}

void Ray::Init(const Vector3d& pos, const Vector3d& dir)
{
	m_position.Init(pos);
	m_direction = dir.Normalize();
}

bool Ray::IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const
{
	switch (rhs.GetType())
	{
	case WorldType::CT_Point:
		return IsCollisionPoint(static_cast<const Point&>(rhs), pointOfIntersect);
	case WorldType::CT_Sphere:
		return IsCollisionSphere(static_cast<const Sphere&>(rhs), pointOfIntersect);
	case WorldType::CT_Ray:
		return IsCollisionRay(static_cast<const Ray&>(rhs), pointOfIntersect);
	default:
		cout << "DEFAULT IsCollision" << endl;
		break;
	}

	return false;
}

bool Ray::IsCollisionPoint(const Point& rhs, Vector3d& pointOfIntersect) const
{
	if (m_position == rhs.GetPosition())
	{
		return true;
	}

	Vector3d dxc = (rhs.GetPosition() - m_position.GetPosition()).Normalize();
	return dxc == m_direction;
}

bool Ray::IsCollisionSphere(const Sphere& rhs, Vector3d& pointOfIntersect) const
{
	const Vector3d vecToSphere = (rhs.GetPosition() - GetPosition());
	const double Tca = vecToSphere.DotProduct(m_direction);

	// sphere is behind ray
	if (Tca < 0)
	{
		// only way we can still hit is if ray is in sphere
		//return (vecToSphere.lengthSqr() <= rhs.GetRadiusSqr());

		// don't care if we're in the sphere.
		return false;
	}

	const double dSqr = vecToSphere.DotProduct(vecToSphere) - Tca*Tca;

	if (dSqr > rhs.GetRadiusSqr())
	{
		return false;
	}

	return true;
}

bool Ray::IsCollisionRay(const Ray& rhs, Vector3d& pointOfIntersect) const
{
	printf("IsCollisionRay not implemented!\n");
	return true;
}



TEST(PointCollision, Ray)
{
	Ray forwards(Vector3d(1, 1, 1), Vector3d(0, 0, 1));
	Ray backwards(Vector3d(1, 1, 1), Vector3d(0, 0, -1));
	Point test1(Vector3d(1, 1, 1));		// origin
	Point test2(Vector3d(1, 1, 2));		// in front
	Point test3(Vector3d(1, 1, 0));		// behind
	Point test4(Vector3d(1, 1, -1));	// behind
	Point test5(Vector3d(2, 2, 2));		// not in line
	
	// forwards
	EXPECT_TRUE(forwards.IsCollision(test1, Vector3d()));
	EXPECT_TRUE(forwards.IsCollision(test2, Vector3d()));
	EXPECT_FALSE(forwards.IsCollision(test3, Vector3d()));
	EXPECT_FALSE(forwards.IsCollision(test4, Vector3d()));
	EXPECT_FALSE(forwards.IsCollision(test5, Vector3d()));

	//backwards
	EXPECT_TRUE(backwards.IsCollision(test1, Vector3d()));
	EXPECT_FALSE(backwards.IsCollision(test2, Vector3d()));
	EXPECT_TRUE(backwards.IsCollision(test3, Vector3d()));
	EXPECT_TRUE(backwards.IsCollision(test4, Vector3d()));
	EXPECT_FALSE(backwards.IsCollision(test5, Vector3d()));
}

TEST(SphereCollision, Ray)
{
	Ray ray(Vector3d(1, 1, -10), Vector3d(0, 0, 1));
	Sphere test1(Vector3d(1, 1, 2), 1);		// ray crosses center
	Sphere test2(Vector3d(1, 0, 2), 1);		// one point collision
	Sphere test3(Vector3d(.5, .5, 1), 1);	// two point collision
	Sphere test4(Vector3d(1, 1, -9), 1);	// Ray exists in Sphere, before center
	Sphere test5(Vector3d(1, 1, -10.5), 1);	// Ray exists in Sphere, after center
	Sphere test6(Vector3d(5, 5, 5), 1);		// no collision
	Sphere test7(Vector3d(-1, -1, -20), 1);	// behind ray
	

	EXPECT_TRUE(ray.IsCollision(test1, Vector3d()));
	EXPECT_TRUE(ray.IsCollision(test2, Vector3d()));
	EXPECT_TRUE(ray.IsCollision(test3, Vector3d()));
	EXPECT_TRUE(ray.IsCollision(test4, Vector3d()));
	EXPECT_FALSE(ray.IsCollision(test5, Vector3d()));	// set to true if we ever care about rays being in front of sphere origin, but still in sphere
	EXPECT_FALSE(ray.IsCollision(test6, Vector3d()));
	EXPECT_FALSE(ray.IsCollision(test7, Vector3d()));
}

TEST(RayCollision, Ray)
{
	Ray ray(Vector3d(1, 1, -10), Vector3d(0, 0, 1));
	Ray test1(Vector3d(1, 1, 10), Vector3d(0, 0, -1));	// straight on collision
	Ray test2(Vector3d(1, 0, -10), Vector3d(0, 1, 0));	// 90 degree angle
	Ray test3(Vector3d(5, 5, 5), Vector3d(1, 1, 1));	// no collision

	//EXPECT_TRUE(ray.IsCollision(test1));
	//EXPECT_TRUE(ray.IsCollision(test2));
	//EXPECT_FALSE(ray.IsCollision(test3));
}