#pragma once
#include "Object.h"
#include <string>

class ErrorObject :
	public Object
{
public:
	ErrorObject();
	ErrorObject(const std::string& error);
	virtual ~ErrorObject();
	virtual void Init(const DeserializeData& data){}

	inline const std::string& GetError() const{ return m_errorMessage; }
private:
	std::string m_errorMessage;
};

