#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>
#include <math.h>
#include "Sphere.h"
#include "DeserializeData.h"
#include "Ray.h"

using namespace std;

Sphere::Sphere()
: CollidableObject(ObjectType::CT_Sphere)
, m_position()
, m_radius(0)
, m_radiusSqr(0)
{
}

Sphere::Sphere(const Vector3d& inPos, double inRadius)
: CollidableObject(ObjectType::CT_Sphere)
, m_position()
, m_radius(0)
, m_radiusSqr(0)
{
	Init(inPos, inRadius);
}

Sphere::~Sphere(){}

void Sphere::Init(const Vector3d& inPos, double inRadius)
{
	m_position.Init(inPos);

	m_radius = inRadius;
	m_radiusSqr = (inRadius*inRadius);
}

void Sphere::Init(const DeserializeData& data)
{
	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapDouble.at(DeserializeData::RADIUS));

	m_material.Init(data);
}