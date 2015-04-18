#include "stdafx.h"
#include "Light.h"
#include "DeserializeData.h"


Light::Light()
:CollidableObject(CT_Light)
{
}


Light::~Light()
{
}

void Light::Init(const DeserializeData& data)
{
	m_position = data.m_mapVector.at(DeserializeData::POSITION);

	m_material.Init(data);
}

const Vector3d& Light::GetNormal(const Vector3d& intersectPoint) const
{
	return m_position;
}
