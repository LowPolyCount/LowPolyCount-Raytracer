#include "stdafx.h"
#include <gtest\gtest.h>
#include <assert.h>
#include "InfinitePlane.h"
#include "Ray.h"
#include "DeserializeData.h"

using namespace std;

InfinitePlane::InfinitePlane()
:CollidableObject(CT_InfinitePlane)
{
}

InfinitePlane::InfinitePlane(const Vector3d& pos, const Vector3d& dir)
: CollidableObject(CT_InfinitePlane)
{
	Init(pos, dir);
}

InfinitePlane::~InfinitePlane()
{

}

void InfinitePlane::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapVector.at(DeserializeData::DIRECTION));

	m_material.Init(data);
}

void InfinitePlane::Init(const Vector3d& pos, const Vector3d& dir)
{
	m_position = pos;
	m_direction = dir.Normalize();
}

bool InfinitePlane::operator == (const InfinitePlane& rhs) const
{
	return m_position == rhs.GetPosition() && m_direction == rhs.GetDirection();
}