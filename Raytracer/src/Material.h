#pragma once
#include "RaytracerTypes.h"
#include "Vector3d.h"

struct DeserializeData;

class Material
{
public:
	Material();
	~Material();
	void Init(const DeserializeData& data);
	RGBA GetColor() const { return m_color; }
	const Vector3d& GetLighting() const { return m_lighting; }
private:
	void ConvertColor(const Vector3d& material);

	RGBA m_color;
	Vector3d m_lighting;
};