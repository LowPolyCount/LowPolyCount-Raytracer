#include "stdafx.h"
#include <iostream>
#include "LpcMath.h"
/*#include "Vector3d.h"
#include "CollidableObject.h"*/


using namespace std;

/*LpcMath::LpcMath()
{
}


LpcMath::~LpcMath()
{
}*/

bool LpcMath::IsCollision(const CollidableObject& obj1, const CollidableObject& obj2, Vector3d& pointOfIntersect)
{
	if (obj2.GetType() == CollidableObject::CT_Ray && obj2.GetType() != CollidableObject::CT_Ray)
	{
		return IsCollision(obj2, obj1, pointOfIntersect);
	}

	switch (obj2.GetType())
	{
	case CollidableObject::CT_Point:
		return IsCollisionPoint(static_cast<const Ray&>(obj1), static_cast<const Point&>(obj2), pointOfIntersect);
	case CollidableObject::CT_Sphere:
		return IsCollisionSphere(static_cast<const Ray&>(obj1), static_cast<const Sphere&>(obj2), pointOfIntersect);
	case CollidableObject::CT_Ray:
		return IsCollisionRay(static_cast<const Ray&>(obj1), static_cast<const Ray&>(obj2), pointOfIntersect);
	case CollidableObject::CT_InfinitePlane:
		return IsCollisionInfinitePlane(static_cast<const Ray&>(obj1), static_cast<const InfinitePlane&>(obj2), pointOfIntersect);
	default:
		cout << "DEFAULT IsCollision" << endl;
		break;
	}

	return false;
}


bool LpcMath::IsCollisionPoint(const Ray& obj1, const Point& rhs, Vector3d& pointOfIntersect)
{
	if (obj1.GetPosition() == rhs.GetPosition())
	{
		return true;
	}

	const Vector3d dxc = (rhs.GetPosition() - obj1.GetPosition()).Normalize();
	return dxc == obj1.GetDirection();
}

bool LpcMath::IsCollisionSphere(const Ray& obj1, const Sphere& rhs, Vector3d& pointOfIntersect)
{
	const Vector3d L = rhs.GetPosition() - obj1.GetPosition();
	const double Tca = L.DotProduct(obj1.GetDirection());

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
		pointOfIntersect = obj1.GetPosition() + obj1.GetDirection() * t;
		Vector3d pointOfIntersect2 = obj1.GetPosition() + obj1.GetDirection() * tt;
	}
	else
	{
		pointOfIntersect = obj1.GetPosition() + obj1.GetDirection() * tt;
	}

	return true;
}

bool LpcMath::IsCollisionRay(const Ray& obj1, const Ray& obj2, Vector3d& pointOfIntersect)
{
	cout << "IsCollisionRay not implemented!" << endl;
	assert(false);
	return true;
}

bool LpcMath::IsCollisionInfinitePlane(const Ray& obj1, const InfinitePlane& obj2, Vector3d& pointOfIntersect)
{
	const Vector3d u = obj1.GetPosition();
	const Vector3d ur = obj1.GetDirection();
	const Vector3d p = obj2.GetPosition();
	const Vector3d n = obj2.GetDirection();
	const Vector3d pr = u - obj2.GetPosition();

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
	EXPECT_TRUE(LpcMath::IsCollision(forwards, test1, Vector3d()));
	EXPECT_TRUE(LpcMath::IsCollision(forwards, test2, Vector3d()));
	EXPECT_FALSE(LpcMath::IsCollision(forwards, test3, Vector3d()));
	EXPECT_FALSE(LpcMath::IsCollision(forwards, test4, Vector3d()));
	EXPECT_FALSE(LpcMath::IsCollision(forwards, test5, Vector3d()));

	//backwards
	EXPECT_TRUE(LpcMath::IsCollision(backwards, test1, Vector3d()));
	EXPECT_FALSE(LpcMath::IsCollision(backwards, test2, Vector3d()));
	EXPECT_TRUE(LpcMath::IsCollision(backwards, test3, Vector3d()));
	EXPECT_TRUE(LpcMath::IsCollision(backwards, test4, Vector3d()));
	EXPECT_FALSE(LpcMath::IsCollision(backwards, test5, Vector3d()));
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


	EXPECT_TRUE(LpcMath::IsCollision(ray, test1, testIntersect1));
	EXPECT_TRUE(LpcMath::IsCollision(ray, test2, testIntersect2));
	EXPECT_TRUE(LpcMath::IsCollision(ray, test3, testIntersect3));
	EXPECT_TRUE(LpcMath::IsCollision(ray, test4, testIntersect4));
	EXPECT_FALSE(LpcMath::IsCollision(ray, test5, testIntersect5));	// set to true if we ever care about rays being in front of sphere origin, but still in sphere
	EXPECT_FALSE(LpcMath::IsCollision(ray, test6, Vector3d()));
	EXPECT_FALSE(LpcMath::IsCollision(ray, test7, Vector3d()));

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

	EXPECT_TRUE(LpcMath::IsCollision(test1, plane, test1Intersect));
	EXPECT_FALSE(LpcMath::IsCollision(test2, plane, Vector3d()));
	EXPECT_TRUE(LpcMath::IsCollision(test3, plane, test3Intersect));
	EXPECT_TRUE(LpcMath::IsCollision(test4, plane, test4Intersect));

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

// enable these if we ever require point-sphere or point-point collisions
/*TEST(PointCollision, Point)
{
	Point test1(Vector3d(1, 1, 1));
	Point test2(Vector3d(5, 5, 5));
	Sphere sphr(Vector3d(.5, .5, .5), 1);

	EXPECT_TRUE(test1.IsCollision(sphr, Vector3d()));
	EXPECT_FALSE(test2.IsCollision(sphr, Vector3d()));
}

TEST(SphereCollision, Point)
{
	Sphere test1(Vector3d(1, 1, 1), 1);
	Sphere test2(Vector3d(5, 5, 5), 10);
	Sphere test3(Vector3d(5, 5, 5), 1);
	Sphere sphr(Vector3d(.5, .5, .5), 1);

	EXPECT_TRUE(test1.IsCollision(sphr, Vector3d()));
	EXPECT_TRUE(test2.IsCollision(sphr, Vector3d()));
	EXPECT_FALSE(test3.IsCollision(sphr, Vector3d()));
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
}*/