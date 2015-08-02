#pragma once
#include "CollidableObject.h"
#include <unordered_map>
#include <functional>
#include <memory>
#include "Object.h"
#include "DeserializeData.h"

class Factory
{
public:
	Factory();
	virtual ~Factory();
	std::shared_ptr<Object> Create(const DeserializeData& data);
private:
	//typedef Object* (*ComponentFactoryFuncPtr)(const DeserializeData& data);
	typedef std::shared_ptr<Object> (*ComponentFactoryFuncPtr)(const DeserializeData& data);
	typedef std::unordered_map<Object::ObjectType, ComponentFactoryFuncPtr> FunctorMap;

	template<class Type>
	void AddType(Object::ObjectType worldType);
	
	FunctorMap m_templateMap;
};

