#include "stdafx.h"
#include "Factory.h"
#include <iostream>
#include "Sphere.h"
#include "Point.h"
#include "Plane.h"
#include "RendererSDL.h"
#include "Camera.h"
#include "Ray.h"
#include "ErrorObject.h"

using namespace std;

static const std::string ERROR("Factory Object Not Found");

template<class Type>
static WorldObject* CreateType(const DeserializeData& data)
{
	WorldObject* returnValue = new Type();
	returnValue->Init(data);
	return returnValue;
}

Factory::Factory()
{
	AddType<Sphere>(WorldObject::WorldType::CT_Sphere);
	AddType<Point>(WorldObject::WorldType::CT_Point);
	AddType<Ray>(WorldObject::WorldType::CT_Ray);
	AddType<Plane>(WorldObject::WorldType::CT_Plane);
	AddType<Camera>(WorldObject::WorldType::CT_Camera);
	AddType<RendererSDL>(WorldObject::WorldType::CT_Image);
}


Factory::~Factory()
{
}

template<class Type>
void Factory::AddType(WorldObject::WorldType worldType)
{
	ComponentFactoryFuncPtr function = &CreateType<Type>;
	m_templateMap.insert(std::make_pair(worldType, function));
}

WorldObject* Factory::Create(const DeserializeData& data)
{
	WorldObject* returnValue = nullptr;
	ComponentFactoryFuncPtr find = m_templateMap.at(data.m_type);

	if (find)
	{
		returnValue = find(data);
	}
	else
	{
		returnValue = new ErrorObject(ERROR);
	}
	
	return returnValue;
}