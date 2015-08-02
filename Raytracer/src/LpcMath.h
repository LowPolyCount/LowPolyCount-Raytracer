#pragma once
#include <vector>
#include "Vector3d.h"
#include "CollidableObject.h"
#include "RaytracerTypes.h"

class Vector3d;
class CollidableObject;
class Ray;
class Sphere;
class Point;
class InfinitePlane;
class Triangle;
class Light;

class LpcMath
{
public:
	//LpcMath();
	//~LpcMath();
	static bool IsCollision(const CollidableObject& obj1, const CollidableObject& obj2, Vector3d& pointOfIntersect);
	static Vector3d DiffuseLighting(const Ray& inRay, const Vector3d& intersectPoint, const Vector3d& normalVec, 
		const std::vector<const std::shared_ptr<Light>>& hitLights, const Vector3d& color, double diffuseFactor, double specularFactor, double shininess);

private:
	static bool IsCollisionPoint(const Ray& obj1, const Point& rhs, Vector3d& pointOfIntersect);
	static bool IsCollisionSphere(const Ray& obj1, const Sphere& rhs, Vector3d& pointOfIntersect);
	static bool IsCollisionRay(const Ray& obj1, const Ray& obj2, Vector3d& pointOfIntersect);
	static bool IsCollisionInfinitePlane(const Ray& obj1, const InfinitePlane& rhs, Vector3d& pointOfIntersect);
	static bool IsCollisionTriangle(const Ray& obj1, const Triangle& rhs, Vector3d& pointOfIntersect);

	static double CalcualteAttenuation(const Light* inLight, const double distanceToLight);

};

