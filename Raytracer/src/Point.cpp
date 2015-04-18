#include "stdafx.h"
#include "gtest\gtest.h"
#include "Point.h"
#include "Sphere.h"
#include "DeserializeData.h"


Point::Point()
: CollidableObject(ObjectType::CT_Point)
, m_position()
{}

Point::Point(const Vector3d& pos)
: CollidableObject(ObjectType::CT_Point)
, m_position()
{
	Init(pos);
}

Point::~Point() {}

void Point::Init(const Vector3d& pos)
{
	m_position = pos;
}

void Point::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION));
}

const Vector3d& Point::GetNormal(const Vector3d& intersectPoint) const
{
	return m_position;
}

