#pragma once
#include "Vector3d.h"
#include "CollidableObject.h"
#include "Ray.h"
#include "Sphere.h"
#include "Point.h"
#include "InfinitePlane.h"

class Vector3d;
class CollidableObject;
class Ray;
class Sphere;
class Point;
class InfinitePlane;

class LpcMath
{
public:
	//LpcMath();
	//~LpcMath();
	static bool IsCollision(const CollidableObject& obj1, const CollidableObject& obj2, Vector3d& pointOfIntersect);

private:
	static bool IsCollisionPoint(const Ray& obj1, const Point& rhs, Vector3d& pointOfIntersect);
	static bool IsCollisionSphere(const Ray& obj1, const Sphere& rhs, Vector3d& pointOfIntersect);
	static bool IsCollisionRay(const Ray& obj1, const Ray& obj2, Vector3d& pointOfIntersect);
	static bool IsCollisionInfinitePlane(const Ray& obj1, const InfinitePlane& rhs, Vector3d& pointOfIntersect);

};
