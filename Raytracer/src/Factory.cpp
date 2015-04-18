#include "stdafx.h"
#include "Factory.h"
#include <iostream>
#include "Sphere.h"
#include "Point.h"
#include "Plane.h"
#include "RendererSDL.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"
#include "ErrorObject.h"
#include "Light.h"

using namespace std;

static const std::string ERROR("Factory Object Not Found");

template<class Type>
static Object* CreateType(const DeserializeData& data)
{
	Object* returnValue = new Type();
	returnValue->Init(data);
	return returnValue;
}

Factory::Factory()
{
	AddType<Sphere>(Object::ObjectType::CT_Sphere);
	AddType<Point>(Object::ObjectType::CT_Point);
	AddType<Ray>(Object::ObjectType::CT_Ray);
	AddType<Plane>(Object::ObjectType::CT_Plane);
	AddType<Camera>(Object::ObjectType::CT_Camera);
	AddType<RendererSDL>(Object::ObjectType::CT_Image);
	AddType<InfinitePlane>(Object::ObjectType::CT_InfinitePlane);
	AddType<Triangle>(Object::ObjectType::CT_Triangle);
	AddType<Light>(Object::ObjectType::CT_Light);
	AddType<ErrorObject>(Object::ObjectType::CT_Unknown);
}


Factory::~Factory()
{
}

template<class Type>
void Factory::AddType(Object::ObjectType worldType)
{
	ComponentFactoryFuncPtr function = &CreateType<Type>;
	m_templateMap.insert(std::make_pair(worldType, function));
}

//TODO: Return a smartpointer
Object* Factory::Create(const DeserializeData& data)
{
	Object* returnValue = nullptr;
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