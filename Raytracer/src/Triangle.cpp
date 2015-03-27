#include "stdafx.h"
#include "Triangle.h"
#include "Vector3d.h"
#include "DeserializeData.h"

Triangle::Triangle()
:CollidableObject(CT_Triangle)
,m_materialProperty()
,m_point1()
,m_point2()
,m_point3()
,m_plane()
{

}


Triangle::~Triangle()
{
}


void Triangle::Init(const Vector3d& inPoint1, const Vector3d& inPoint2, const Vector3d& inPoint3)
{
	m_point1 = inPoint1;
	m_point2 = inPoint2;
	m_point3 = inPoint3;

	const Vector3d planeNormal = (m_point2 - m_point1).CrossProduct(m_point3 - m_point1);

	m_plane.SetDirection(planeNormal);
	m_plane.SetPosition(m_point1);
}

void Triangle::Init(const DeserializeData& data)
{
	Init(	data.m_mapVector.at(DeserializeData::POINT1),
			data.m_mapVector.at(DeserializeData::POINT2),
			data.m_mapVector.at(DeserializeData::POINT3));

	const Vector3d material = data.m_mapVector.at(DeserializeData::MATERIAL);

	m_materialProperty = static_cast<int>(material.x) + (static_cast<int>(material.y) << 8) + (static_cast<int>(material.z) << 16);
}

RGBA Triangle::GetLastMaterialHit() const
{
	return m_materialProperty;
}