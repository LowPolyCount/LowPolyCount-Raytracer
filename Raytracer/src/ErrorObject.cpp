#include "stdafx.h"
#include "ErrorObject.h"


ErrorObject::ErrorObject(const std::string& error)
:m_errorMessage(error)
,WorldObject(WorldObject::WorldType::CT_Error)
{
}


ErrorObject::~ErrorObject()
{
}
