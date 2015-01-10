#pragma warning(disable: 4996)
#include "stdafx.h"
#include "Deserializer.h"
#include "gtest\gtest.h"
#include <iostream>
#include <fstream>

using namespace std;


static const string SPHERE("sphere");
static const string POINT("point");
static const string CAMERA("camera");
static const string IMAGE("image");
static const int STRING_SIZE = 100;

Deserializer::Deserializer()
{
}


Deserializer::~Deserializer()
{
}

bool Deserializer::LoadFile(const string& fileName)
{
	ifstream file;
	file.open(fileName);

	// check
	if (!file.is_open())
	{
		return false;
	}

	char cString[STRING_SIZE];
	while (!file.eof())
	{ 
		file.getline(cString, STRING_SIZE);
		m_data.push_back(DeseralizeLine(string(cString)));
	}
	return true;
}

/*bool Deserializer::LoadYamlFile(const string& fileName)
{
	YAML::Node data = YAML::LoadFile(fileName.c_str());

	for (YAML::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		std::cout << (*it).Type() << endl;
		if ((*it).IsMap())
		{
			DeseralizeYamlObject(*it);
		}
	}

	return true;
}

DeserializeData Deserializer::DeseralizeYamlObject(const YAML::Node data) const
{
	DeserializeData returnData;

	const std::string typeName = (data)["type"].as<std::string>();
	returnData.m_type = FindType(typeName);
	

	/*switch (returnData.m_type)
	{
	case  WorldObject::WorldType::CT_Sphere:
		cout << typeName << endl;
		break;
	default:
		cout << "default" << endl;
		break;
	}

	return returnData;
}*/

DeserializeData Deserializer::DeseralizeLine(const std::string& line) const
{
	DeserializeData returnData;

	// find type string
	const size_t dataStart = line.find_first_of(' ');
	const std::string typeName = line.substr(0, line.find_first_of(' '));
	returnData.m_type = FindType(typeName);

	switch (returnData.m_type)
	{
	case WorldObject::WorldType::CT_Sphere:
		TokenizeSphere(line, dataStart, returnData);
		break;
	case WorldObject::WorldType::CT_Point:
		TokenizePoint(line, dataStart, returnData);
		break;
	case WorldObject::WorldType::CT_Camera:
		TokenizeCamera(line, dataStart, returnData);
		break;
	case WorldObject::WorldType::CT_Image:
		TokenizeImage(line, dataStart, returnData);
		break;
	default:
		break;
	}
	return returnData;
}

WorldObject::WorldType Deserializer::FindType(const std::string& stringType) const
{
	if (stringType.compare(SPHERE) == 0)
	{
		return WorldObject::WorldType::CT_Sphere;
	}
	else if (stringType.compare(POINT) == 0)
	{
		return WorldObject::WorldType::CT_Point;
	}
	else if (stringType.compare(CAMERA) == 0)
	{
		return WorldObject::WorldType::CT_Camera;
	}
	else if (stringType.compare(IMAGE) == 0)
	{
		return WorldObject::WorldType::CT_Image;
	}

	return WorldObject::WorldType::CT_Unknown;
}

void Deserializer::TokenizeSphere(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	const vector<double>& foundNumbers = FindAllNumbers(line, dataStart);

	returnData.m_mapVector[DeserializeData::POSITION] = Vector3d(foundNumbers[0], foundNumbers[1], foundNumbers[2]);
	returnData.m_mapDouble[DeserializeData::RADIUS] = foundNumbers[3];
}

void Deserializer::TokenizePoint(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	const vector<double>& foundNumbers = FindAllNumbers(line, dataStart);

	returnData.m_mapVector[DeserializeData::POSITION] = Vector3d(foundNumbers[0], foundNumbers[1], foundNumbers[2]);
}

void Deserializer::TokenizeCamera(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	const vector<double>& foundNumbers = FindAllNumbers(line, dataStart);

	returnData.m_mapVector[DeserializeData::POSITION] = Vector3d(foundNumbers[0], foundNumbers[1], foundNumbers[2]);
	returnData.m_mapVector[DeserializeData::DIRECTION] = Vector3d(foundNumbers[3], foundNumbers[4], foundNumbers[5]);
}

void Deserializer::TokenizeImage(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	const vector<double>& foundNumbers = FindAllNumbers(line, dataStart);

	returnData.m_mapVector[DeserializeData::POSITION] = Vector3d(foundNumbers[0], foundNumbers[1], 0);
}

vector<double> Deserializer::FindAllNumbers(const std::string& line, const size_t dataStart) const
{
	const size_t size = line.size();
	size_t currentPos = dataStart;
	vector<double> foundNumbers;

	// keep going till we have all numbers
	while (currentPos != string::npos)
	{
		const size_t newPos = line.find(" ", currentPos + 1);
		if (newPos != string::npos)
		{
			foundNumbers.push_back(std::stod(line.substr(currentPos + 1, newPos - currentPos)));
			currentPos = newPos;
		}
		else if (currentPos != string::npos)
		{
			foundNumbers.push_back(std::stod(line.substr(currentPos + 1, size)));
			currentPos = string::npos;
		}
	}

	return foundNumbers;
}


TEST(dataLoad, Deserializer)
{
	Deserializer test;
	ASSERT_TRUE(test.LoadFile("unittest.txt"));

	const std::vector<DeserializeData>& result = test.GetData();

	EXPECT_EQ(result[0].m_type, WorldObject::WorldType::CT_Sphere);
	EXPECT_EQ(result[0].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(0, 1, 2));
	EXPECT_EQ(result[0].m_mapDouble.at(DeserializeData::MapIds::RADIUS), 2);

	EXPECT_EQ(result[1].m_type, WorldObject::WorldType::CT_Point);
	EXPECT_EQ(result[1].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(-1, -2, -3));

	EXPECT_EQ(result[2].m_type, WorldObject::WorldType::CT_Camera);
	EXPECT_EQ(result[2].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(1, 1, 1));
	EXPECT_EQ(result[2].m_mapVector.at(DeserializeData::MapIds::DIRECTION), Vector3d(1, 1, 1));
//	EXPECT_EQ(result[2].m_mapPlane.at(DeserializeData::MapIds::BACKVIEWFRUSTRUM), Plane()

	//Plane planeTest;
	//Plane
//		m_nearPlane.Init(Vector3d(-PLANE_WIDTH + m_position.x, -PLANE_HEIGHT + m_position.y, m_position.z + PLANE_DEPTH),
		//Vector3d(PLANE_WIDTH + m_position.x, PLANE_HEIGHT + m_position.y, m_position.z + PLANE_DEPTH));

	EXPECT_EQ(result[3].m_type, WorldObject::WorldType::CT_Image);
	EXPECT_EQ(result[3].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(256, 640, 0));
}

TEST(FileLoadFail, Deserializer)
{
	Deserializer test;
	ASSERT_FALSE(test.LoadFile("doesNotExist"));
}