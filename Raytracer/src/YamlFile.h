#pragma once
#include "IFileLoader.h"
#include "yaml-cpp\yaml.h"
#include "WorldObject.h"

class YamlFile: public IFileLoader
{
public:
	YamlFile();
	virtual ~YamlFile();
	virtual bool LoadFile(const std::string& fileName);
	virtual bool GetDataFromFile();
	virtual const std::vector<DeserializeData>& GetData() const { return m_data; }
private:
	DeserializeData DeseralizeYamlObject(const YAML::Node data) const;
	void TokenizeSphere(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizePoint(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeCamera(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeImage(const YAML::Node data, DeserializeData& returnData) const;
	WorldObject::WorldType FindType(const std::string& stringType) const;

	YAML::Node						m_yamlData;
	std::vector<DeserializeData>	m_data;
};

