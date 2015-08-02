#include "stdafx.h"
#include <stdlib.h>
#include "Plane.h"
#include "DeserializeData.h"


using namespace std;


Plane::Plane()
:CollidableObject(CT_Plane)
{
}


Plane::~Plane()
{
}

bool Plane::IsCollision(const CollidableObject& rhs, Vector3d& pointOfIntersect) const
{
	assert(true);
	return false;
}

void Plane::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapVector.at(DeserializeData::DIRECTION));
}

void Plane::Init(const Vector3d& upperLeft, const Vector3d& lowerRight)
{
	m_upperLeft = upperLeft;
	m_lowerRight = lowerRight;
}

const Vector3d& Plane::GetNormal(const Vector3d& intersectPoint) const
{
	return m_normal;
}


double Plane::GetWidth() const
{
	//@TODO Only handles Planes that are axis aligned
	return abs(m_upperLeft.y - m_lowerRight.y);
}

double Plane::GetHeight() const
{
	//@TODO Only handles Planes that are axis aligned
	return abs(m_upperLeft.x - m_lowerRight.x);
}

TEST(GetWidthHeight, Plane)
{
	Plane test;
	test.Init(Vector3d(5, -5, -5), Vector3d(1, 1, 1));

	//@TODO Only handles Planes that are axis aligned
	EXPECT_EQ(test.GetWidth(), 6);
	EXPECT_EQ(test.GetHeight(), 4);
}