#include "stdafx.h"
#include "Material.h"
#include "DeserializeData.h"

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
		//const Vector3d material;

		switch ((*i).first)
		{
		case DeserializeData::LIGHTING:
			m_lighting = data.m_mapVector.at(DeserializeData::LIGHTING);
			break;
		case DeserializeData::MATERIAL:
			ConvertColor(data.m_mapVector.at(DeserializeData::MATERIAL));
			break;
		default:
			break;
		}
	}
}

void Material::ConvertColor(const Vector3d& material)
{
	m_color = static_cast<int>(material.x) + (static_cast<int>(material.y) << 8) + (static_cast<int>(material.z) << 16);
}