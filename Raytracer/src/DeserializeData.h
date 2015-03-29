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
		LIGHTING,
		FRONTVIEWFRUSTRUM,
		BACKVIEWFRUSTRUM,
		PLANE1,				// TODO: find better way to represent complex types
		PLANE2,
		POINT1,				// TODO: See if we can build these three points as an array automatically
		POINT2,
		POINT3
	};

	Object::ObjectType				m_type;
	std::map<MapIds, double>		m_mapDouble;
	std::map<MapIds, Vector3d>		m_mapVector;
	std::map<MapIds, std::string>	m_mapString;
};