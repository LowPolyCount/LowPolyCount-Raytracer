#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "LpcMath.h"
#include "Ray.h"
#include "Sphere.h"
#include "Point.h"
#include "InfinitePlane.h"
#include "Triangle.h"
#include "Light.h"


using namespace std;

static const double DIFFUSE_INTENSITY = .10;
static const double AMBIENT_INTENSITY = .20;
static const double SPECULAR_INTENSITY = .50;
static const double SPECULAR_POWER = 8.0f;     // The specular power, used as 'glossiness' factor. 

/*LpcMath::LpcMath()
{
}


LpcMath::~LpcMath()
{
}*/

double LpcMath::CalcualteAttenuation(const shared_ptr<Light> inLight, const double distanceToLight)
{
	const double a = 1;
	const double b = 1;
	const double c = 1;
	return 1 / (a + b*distanceToLight + c*distanceToLight*distanceToLight);
}

Vector3d LpcMath::DiffuseLighting(const Ray& inRay, const Vector3d& intersectPoint, const Vector3d& surfaceNormal, const vector<const shared_ptr<Light>>& hitLights,
	const Vector3d& surfaceColor, double diffuseFactor, double specularFactor, double shininess)
{
	Vector3d returnValue(0, 0, 0);
	const Vector3d viewingDir = inRay.GetDirection();
	const Vector3d dirToEye = -(inRay.GetDirection());

	//const Vector3d ReflectedVector = inRay.GetDirection() - (surfaceNormal * 2 * (inRay.GetDirection().DotProduct(surfaceNormal)));

	// ambient color
	const Vector3d ambientColor = (surfaceColor)*AMBIENT_INTENSITY;

	returnValue = ambientColor;
	
	for (auto i = hitLights.begin(); i != hitLights.end(); ++i)
	{		
		const double toLightDistance = ((*i)->GetPosition() - intersectPoint).length();
		Vector3d dirToLight = ((*i)->GetPosition() - intersectPoint);
		dirToLight.NormalizeVector();
		const Vector3d lightColor = (*i)->GetMaterial().GetColor();

		

		const double attenuation = CalcualteAttenuation(*i, toLightDistance);

		// diffuse
		const double diffuseDotProduct = std::max((surfaceNormal).DotProduct(dirToLight), static_cast<double>(0));
		const Vector3d diffuseColor = lightColor*diffuseDotProduct*DIFFUSE_INTENSITY;

		// specular
		Vector3d halfDir = (dirToLight + -dirToEye);
		halfDir.NormalizeVector;
		double specAngle = max(halfDir.DotProduct(surfaceNormal), 0.0);
		double specular = 0;// pow(specAngle, 256);

		//const Vector3d halfVector = (dirToEye + (-dirToLight)).Normalize();
		//const Vector3d reflect = -dirToEye - surfaceNormal*(2*(-dirToEye.DotProduct(surfaceNormal)));
		//const Vector3d reflect = viewingDir - surfaceNormal*(2 * (viewingDir.DotProduct(surfaceNormal)));
		//const Vector3d halfVector = ((dirToEye + dirToLight)) / (dirToEye.length() + dirToLight.length()); //.Normalize();
		//const Vector3d SpecularLighting = SpecularColor * (SpecularColorOfLight * ((NormalVector dot HalfWayVector) power SpecularReflectionPower) * Attentuation * Spotlight)
		//const Vector3d specularColor = lightColor*pow(max(0.0, reflect.DotProduct(surfaceNormal)), 32)*SPECULAR_INTENSITY;
		const Vector3d specularColor = lightColor*specular;

		returnValue += diffuseColor + specularColor;
	}
	return returnValue;
}


bool LpcMath::IsCollision(const CollidableObject& obj1, const CollidableObject& obj2, Vector3d& pointOfIntersect)
{
	// always make sure ray is always obj1 
	if (obj1.GetType() != CollidableObject::CT_Ray && obj2.GetType() == CollidableObject::CT_Ray)
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
	case CollidableObject::CT_Triangle:
		return IsCollisionTriangle(static_cast<const Ray&>(obj1), static_cast<const Triangle&>(obj2), pointOfIntersect);
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

	Vector3d dxc = (rhs.GetPosition() - obj1.GetPosition());
	dxc.NormalizeVector();
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
	cout << "ERROR: IsCollisionRay not implemented!" << endl;
	return true;
}

bool LpcMath::IsCollisionInfinitePlane(const Ray& obj1, const InfinitePlane& obj2, Vector3d& pointOfIntersect)
{
	const double denom = obj2.GetDirection().DotProduct(obj1.GetDirection());
	if (abs(denom) > DBL_EPSILON)
	{
		const double t = (obj2.GetPosition() - obj1.GetPosition()).DotProduct(obj2.GetDirection()) / denom;
		if (t >= 0) 
		{
			pointOfIntersect = obj1.GetPosition() + obj1.GetDirection()*t;
			return true;
		}
	}
	return false;
}

bool LpcMath::IsCollisionTriangle(const Ray& obj1, const Triangle& rhs, Vector3d& pointOfIntersect)
{
	const InfinitePlane& plane = rhs.GetPlane();
	const Vector3d& normalVec = plane.GetDirection();

	if (IsCollisionInfinitePlane(obj1, plane, pointOfIntersect))

	{
		// in plane, now check if intersect point is in triangle
		bool hit1 = (rhs.GetPoint2() - rhs.GetPoint1()).CrossProduct(pointOfIntersect - rhs.GetPoint1()).DotProduct(normalVec) >= 0;
		bool hit2 = (rhs.GetPoint3() - rhs.GetPoint2()).CrossProduct(pointOfIntersect - rhs.GetPoint2()).DotProduct(normalVec) >= 0;
		bool hit3 = (rhs.GetPoint1() - rhs.GetPoint3()).CrossProduct(pointOfIntersect - rhs.GetPoint3()).DotProduct(normalVec) >= 0;
		return hit1 && hit2 && hit3;
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

	Ray test5(Vector3d(0, -10, 0), Vector3d(0, 1, 0));	// opposite side of test1
	Vector3d test5Intersect;


	EXPECT_TRUE(LpcMath::IsCollision(test1, plane, test1Intersect));
	EXPECT_FALSE(LpcMath::IsCollision(test2, plane, Vector3d()));
	EXPECT_TRUE(LpcMath::IsCollision(test3, plane, test3Intersect));
	EXPECT_TRUE(LpcMath::IsCollision(test4, plane, test4Intersect));
	EXPECT_TRUE(LpcMath::IsCollision(test5, plane, test5Intersect));

	EXPECT_EQ(Vector3d(0, 0, 0), test1Intersect);
	EXPECT_EQ(Vector3d(0, 0, 0), test3Intersect);
	EXPECT_EQ(Vector3d(-5, 0, -5), test4Intersect);
	EXPECT_EQ(Vector3d(0, 0, 0), test5Intersect);
}

TEST(TriangleCollision, Ray)
{
	Ray ray(Vector3d(0, 0, -10), Vector3d(0, 0, 1));

	Triangle test1;		// no collision
	Triangle test2;		// collision

	test1.Init(Vector3d(5, 5, 5),
		Vector3d(3, 3, 5),
		Vector3d(3, 8, 5));

	test2.Init(Vector3d(0, 0, 0),
		Vector3d(-5, -5, 0),
		Vector3d(5, 0, 0));

	Vector3d testIntersection;


	EXPECT_FALSE(LpcMath::IsCollision(test1, ray, Vector3d()));
	EXPECT_TRUE(LpcMath::IsCollision(test2, ray, testIntersection));

	EXPECT_EQ(Vector3d(0, 0, 0), testIntersection);
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