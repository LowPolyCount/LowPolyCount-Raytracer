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

static const string ERROR("Factory Object Not Found");

// this function does the actual creation and init of a given object type
template<class Type>
static shared_ptr<Object> CreateType(const DeserializeData& data)
{
	shared_ptr<Object> returnValue = make_shared<Type>();
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

// associate a templated creation function with an object type
template<class Type>
void Factory::AddType(Object::ObjectType worldType)
{
	ComponentFactoryFuncPtr function = &CreateType<Type>;
	m_templateMap.insert(make_pair(worldType, function));
}

shared_ptr<Object> Factory::Create(const DeserializeData& data)
{
	ComponentFactoryFuncPtr objectCreateFunction = m_templateMap.at(data.m_type);

	if (objectCreateFunction)
	{
		return objectCreateFunction(data);
	}

	return make_shared<ErrorObject>(ERROR);
}