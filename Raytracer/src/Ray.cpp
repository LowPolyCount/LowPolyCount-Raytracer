#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>
#include <math.h>
#include "Ray.h"
#include "Sphere.h"
#include "Point.h"
#include "InfinitePlane.h"
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
	case WorldType::CT_InfinitePlane:
		return IsCollisionInfinitePlane(static_cast<const InfinitePlane&>(rhs), pointOfIntersect);
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
	//const Vector3d vecToSphere = (rhs.GetPosition() - GetPosition());
	//const double Tca = vecToSphere.DotProduct(m_direction);

/*	// sphere is behind ray
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

	return true;*/

	/*
	Calculate the intersection of a ray and a sphere
	The line segment is defined from p1 to p2
	The sphere is of radius r and centered at sc
	There are potentially two points of intersection given by
	p = p1 + mu1 (p2 - p1)
	p = p1 + mu2 (p2 - p1)
	Return FALSE if the ray doesn't intersect the sphere.
	*/
//	int RaySphere(XYZ p1, XYZ p2, XYZ sc, double r, double *mu1, double *mu2)
	/*double a, b, c;
	double bb4ac;
	//XYZ dp;	// direction
	Vector3d dp = GetDirection();
	Vector3d p1 = GetPosition();
	Vector3d p2 = GetPosition() * 1000;
	Vector3d sc = rhs.GetPosition();
	//Vector3d 

	//dp.x = p2.x - p1.x;
	//dp.y = p2.y - p1.y;
	//dp.z = p2.z - p1.z;

	a = dp.DotProduct(dp);
	b = 2 * dp.DotProduct(GetPosition() - rhs.GetPosition());
	c = sc.DotProduct(sc);
	c += p1.DotProduct(p1);
	c -= 2*sc.DotProduct(p1);
	//a = dp.x * dp.x + dp.y * dp.y + dp.z * dp.z;
	//b = 2 * (dp.x * (p1.x - sc.x) + dp.y * (p1.y - sc.y) + dp.z * (p1.z - sc.z));
	//c = sc.x * sc.x + sc.y * sc.y + sc.z * sc.z;
	//c += p1.x * p1.x + p1.y * p1.y + p1.z * p1.z;
	//c -= 2 * (sc.x * p1.x + sc.y * p1.y + sc.z * p1.z);
	c -= rhs.GetRadiusSqr();
	bb4ac = b * b - 4 * a * c;
	if (std::abs(a) < .0001 || bb4ac < 0) 
	{
		return false;
	}

	const double dist1 = (-b + sqrt(bb4ac)) / (2 * a);
	const double dist2 = (-b - sqrt(bb4ac)) / (2 * a);

	if (dist1 < dist2 && dist1 >= 0)
	{
		pointOfIntersect = GetPosition() + GetDirection()*dist1;
	}
	else
	{
		pointOfIntersect = GetPosition() + GetDirection()*dist2;
	}

	return true;*/
	// END Algebraic method

	const Vector3d L = rhs.GetPosition() - GetPosition();
	const double Tca = L.DotProduct(GetDirection());
	
	if (Tca < 0)
	{
		return false;
	}

	const double d2 = L.DotProduct(L) - Tca*Tca;

	if (d2 > rhs.GetRadiusSqr())
	{
		return false;
	}

	const double Thc = std::sqrt(rhs.GetRadiusSqr() - d2);
	const double t = Tca - Thc;
	const double tt = Tca + Thc;

	if (t < tt && t >= 0)
	{
		pointOfIntersect = GetPosition() + GetDirection() * t;
		Vector3d pointOfIntersect2 = GetPosition() + GetDirection() * tt;
	}
	else
	{
		pointOfIntersect = GetPosition() + GetDirection() * tt;
	}

	return true;
}

bool Ray::IsCollisionRay(const Ray& rhs, Vector3d& pointOfIntersect) const
{
	cout << "IsCollisionRay not implemented!" << endl;
	assert(false);
	return true;
}

bool Ray::IsCollisionInfinitePlane(const InfinitePlane& rhs, Vector3d& pointOfIntersect) const
{
	const Vector3d u = GetPosition();
	const Vector3d ur = GetDirection();
	const Vector3d p = rhs.GetPosition();
	const Vector3d n = rhs.GetDirection();
	const Vector3d pr = u - rhs.GetPosition();
	
	const double k = -(n.DotProduct(pr) / n.DotProduct(ur));

	if (k >= 0)
	{
		pointOfIntersect = u + ur*k;
		return true;
	}

	return false;
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
	Vector3d testIntersect1;
	Vector3d testIntersect2;
	Vector3d testIntersect3;
	Vector3d testIntersect4;
	Vector3d testIntersect5;
	

	EXPECT_TRUE(ray.IsCollision(test1, testIntersect1));
	EXPECT_TRUE(ray.IsCollision(test2, testIntersect2));
	EXPECT_TRUE(ray.IsCollision(test3, testIntersect3));
	EXPECT_TRUE(ray.IsCollision(test4, testIntersect4));
	EXPECT_FALSE(ray.IsCollision(test5, testIntersect5));	// set to true if we ever care about rays being in front of sphere origin, but still in sphere
	EXPECT_FALSE(ray.IsCollision(test6, Vector3d()));
	EXPECT_FALSE(ray.IsCollision(test7, Vector3d()));

	EXPECT_EQ(testIntersect1, Vector3d(1, 1, 1));
	EXPECT_EQ(testIntersect2, Vector3d(1, 1, 2));
	EXPECT_EQ(testIntersect3, Vector3d(1, 1, 0.29289321881345209));
	EXPECT_EQ(testIntersect4, Vector3d(1, 1, -10));
	//EXPECT_EQ(testIntersect5, Vector3d(1, 1, -10));
}

TEST(InfinitePlaneCollision, Ray)
{
	InfinitePlane plane(Vector3d(0, 0, 0), Vector3d(0, 1, 0));

	Ray test1(Vector3d(0, 10, 0), Vector3d(0, -1, 0)); // perpendicular
	Vector3d test1Intersect;

	Ray test2(Vector3d(5, 5, 5), Vector3d(1, 1, 1));	// no collision

	Ray test3(Vector3d(5, 5, 5), Vector3d(-1, -1, -1));	// 45 degree angle
	Vector3d test3Intersect;

	Ray test4(Vector3d(-5, -5, -5), Vector3d(0, 1, 0));
	Vector3d test4Intersect;

	EXPECT_TRUE(test1.IsCollision(plane, test1Intersect));
	EXPECT_FALSE(test2.IsCollision(plane, Vector3d()));
	EXPECT_TRUE(test3.IsCollision(plane, test3Intersect));
	EXPECT_TRUE(test4.IsCollision(plane, test4Intersect));

	EXPECT_EQ(Vector3d(0, 0, 0), test1Intersect);
	EXPECT_EQ(Vector3d(0, 0, 0), test3Intersect);
	EXPECT_EQ(Vector3d(-5, 0, -5), test4Intersect);
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