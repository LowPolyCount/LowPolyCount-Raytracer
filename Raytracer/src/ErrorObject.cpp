#include "stdafx.h"
#include "ErrorObject.h"

ErrorObject::ErrorObject()
:Object(Object::ObjectType::CT_Error)
,m_errorMessage("Unknown Type Found")
{

}

ErrorObject::ErrorObject(const std::string& error)
:m_errorMessage(error)
,Object(Object::ObjectType::CT_Error)
{
}


ErrorObject::~ErrorObject()
{
}
