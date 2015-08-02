#pragma once
#include "RaytracerTypes.h"
#include "Vector3d.h"
#include <memory>

struct DeserializeData;
struct IntersectionRecordLight;

class Ray;
class Light;
class Material
{
public:
	Material();
	~Material();
	void Init(const DeserializeData& data);
	const Vector3d& GetColor() const { return m_color; }
	const Vector3d& GetLighting() const { return m_lighting; } 
	Vector3d CalculateMaterialHit(const Ray& testRay, const Vector3d& intersectPoint, const Vector3d& normalVec, const std::vector<const std::shared_ptr<Light>>& hitLights) const;
private:
	Vector3d m_color;
	Vector3d m_lighting;
};