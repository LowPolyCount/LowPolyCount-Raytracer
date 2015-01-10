#pragma once
#include "CollidableObject.h"
#include <unordered_map>
#include <functional>
#include "WorldObject.h"
#include "DeserializeData.h"

class Factory
{
public:
	Factory();
	virtual ~Factory();
	WorldObject* Create(const DeserializeData& data);
private:
	typedef WorldObject* (*ComponentFactoryFuncPtr)(const DeserializeData& data);
	typedef std::unordered_map<WorldObject::WorldType, ComponentFactoryFuncPtr> FunctorMap;

	template<class Type>
	void AddType(WorldObject::WorldType worldType);
	
	FunctorMap m_templateMap;
};

