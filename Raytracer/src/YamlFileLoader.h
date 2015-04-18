#pragma once
#include "IFileLoader.h"
#include "yaml-cpp\yaml.h"
#include "Object.h"

class YamlFileLoader: public IFileLoader
{
public:
	YamlFileLoader();
	virtual ~YamlFileLoader();
	virtual bool LoadFile(const std::string& fileName);
	virtual bool GetDataFromFile();
	virtual const std::vector<DeserializeData>& GetData() const { return m_data; }
private:
	DeserializeData DeseralizeYamlObject(const YAML::Node data) const;
	void TokenizeSphere(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizePoint(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeCamera(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeImage(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeInfinitePlane(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeTriangle(const YAML::Node data, DeserializeData& returnData) const;
	void TokenizeLight(const YAML::Node data, DeserializeData& returnData) const;

	YAML::Node						m_yamlData;
	std::vector<DeserializeData>	m_data;
};

