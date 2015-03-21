#pragma once
#include <string>
#include <vector>
#include "IFileLoader.h"
#include "DeserializeData.h"
#include "Object.h"

//@TODO: Remove file. Not longer used.
class Deserializer: public IFileLoader
{
public:
	Deserializer();
	virtual ~Deserializer();
	virtual bool LoadFile(const std::string& fileName);
	virtual bool GetDataFromFile() { return false; }
	bool LoadYamlFile(const std::string& fileName);
	virtual const std::vector<DeserializeData>& GetData() const { return m_data; }
protected:
	//DeserializeData Deserializer::DeseralizeYamlObject(const YAML::Node data) const;
	DeserializeData DeseralizeLine(const std::string& line) const;
	void TokenizeSphere(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	void TokenizePoint(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	void TokenizeCamera(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	void TokenizeImage(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	Object::ObjectType FindType(const std::string& stringType) const;
	std::vector<double> FindAllNumbers(const std::string& line, const size_t dataStart) const;

	std::vector<DeserializeData> m_data;
};

