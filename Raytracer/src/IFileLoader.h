#pragma once

/**
An interface that defines data that will be loaded in from a file and converted to the DeserializeData format
*/
#include <vector>
#include "DeserializeData.h"

class IFileLoader
{
public:
	IFileLoader();
	virtual ~IFileLoader();
	virtual bool GetDataFromFile() = 0;
	virtual bool LoadFile(const std::string& fileName) = 0;
	virtual const std::vector<DeserializeData>& GetData() const = 0;

};

