#pragma once

#include <map>
#include <string>
#include "Vector3d.h"
#include "Object.h"

class Plane;
struct DeserializeData
{
	enum MapIds
	{
		POSITION = 0,
		DIRECTION,
		RADIUS,
		MATERIAL,
		FRONTVIEWFRUSTRUM,
		BACKVIEWFRUSTRUM,
		PLANE1,				// TODO: find better way to represent complex types
		PLANE2
	};

	Object::ObjectType				m_type;
	std::map<MapIds, double>		m_mapDouble;
	std::map<MapIds, Vector3d>		m_mapVector;
	std::map<MapIds, std::string>	m_mapString;
};