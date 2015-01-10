#pragma once

#include <map>
#include <string>
#include "Vector3d.h"
#include "WorldObject.h"

class Plane;
struct DeserializeData
{
	enum MapIds
	{
		POSITION = 0,
		DIRECTION,
		RADIUS,
		FRONTVIEWFRUSTRUM,
		BACKVIEWFRUSTRUM,
		PLANE1,				// TODO: find better way to represent complex types
		PLANE2
	};

	WorldObject::WorldType			m_type;
	std::map<MapIds, double>		m_mapDouble;
	std::map<MapIds, Vector3d>		m_mapVector;
	std::map<MapIds, std::string>	m_mapString;
};