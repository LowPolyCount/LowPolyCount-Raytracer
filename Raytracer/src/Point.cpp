#include "stdafx.h"
#include "gtest\gtest.h"
#include "Point.h"
#include "Sphere.h"
#include "DeserializeData.h"


Point::Point()
: CollidableObject(WorldType::CT_Point)
, m_position()
{}

Point::Point(const Vector3d& pos)
: CollidableObject(WorldType::CT_Point)
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

