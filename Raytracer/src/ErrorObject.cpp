#include "stdafx.h"
#include "ErrorObject.h"

ErrorObject::ErrorObject()
:WorldObject(WorldObject::WorldType::CT_Error)
,m_errorMessage("Unknown Type Found")
{

}

ErrorObject::ErrorObject(const std::string& error)
:m_errorMessage(error)
,WorldObject(WorldObject::WorldType::CT_Error)
{
}


ErrorObject::~ErrorObject()
{
}
