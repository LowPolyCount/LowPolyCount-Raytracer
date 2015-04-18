#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>
#include <math.h>
#include "Ray.h"
#include "Sphere.h"
#include "Point.h"
#include "InfinitePlane.h"
#include "DeserializeData.h"


using namespace std;

Ray::Ray()
:CollidableObject(CT_Ray)
{
}

Ray::Ray(const Vector3d& pos, const Vector3d& dir)
: CollidableObject(CT_Ray)
{
	Init(pos, dir);
}

Ray::~Ray()
{
}

const Vector3d& Ray::GetNormal(const Vector3d& intersectPoint) const
{
	return m_direction;
}

bool Ray::operator ==(const Ray& rhs) const
{
	return rhs.GetPosition() == this->GetPosition() && rhs.GetDirection() == this->GetDirection();
}

void Ray::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapVector.at(DeserializeData::DIRECTION));
}

void Ray::Init(const Vector3d& pos, const Vector3d& dir)
{
	m_position.Init(pos);
	m_direction = dir.Normalize();
}

void Ray::MoveByDelta(double delta)
{
	m_position = m_position.GetPosition() + (m_direction*delta);
}