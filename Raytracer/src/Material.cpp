#include "stdafx.h"
#include "Material.h"
#include "DeserializeData.h"
#include "WorldManager.h"
#include "LpcMath.h"

using namespace std;

Material::Material()
{

}
Material::~Material()
{

}

void Material::Init(const DeserializeData& data)
{
	for (auto i = data.m_mapVector.begin(); i != data.m_mapVector.end(); ++i)
	{
		switch ((*i).first)
		{
		case DeserializeData::LIGHTING:
			m_lighting = data.m_mapVector.at(DeserializeData::LIGHTING);
			break;
		case DeserializeData::MATERIAL:
			m_color = data.m_mapVector.at(DeserializeData::MATERIAL);
			m_color.NormalizeColorValues();
			break;
		default:
			break;
		}
	}
}

Vector3d Material::CalculateMaterialHit(const Ray& inRay, const Vector3d& intersectPoint, const Vector3d& normalVec, const vector<const shared_ptr<Light>>& hitLights) const
{
	return LpcMath::DiffuseLighting(inRay, intersectPoint, normalVec, hitLights, this->GetColor(), m_lighting.x, m_lighting.y, m_lighting.z);
}