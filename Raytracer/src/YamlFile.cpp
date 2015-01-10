#include "stdafx.h"
#include "YamlFile.h"
#include "Vector3d.h"

using namespace std;

static const string SPHERE = "sphere";
static const string POINT = "point";
static const string CAMERA = "camera";
static const string IMAGE = "image";

static const string VAR_X = "x";
static const string VAR_Y = "y";
static const string VAR_Z = "z";
static const string DIR_X = "dirx";
static const string DIR_Y = "diry";
static const string DIR_Z = "dirz";
static const string RADIUS = "radius";
static const string TYPE = "type";
static const string POSITION = "position";
static const string DIRECTION = "direction";
static const string RESOLUTION = "resolution";
static const string NEARPLANE = "nearPlane";
static const string FARPLANE = "farPlane";

//@TODO: JMG - put checks around where we get data to prevent unauthorized access

namespace YAML
{
	template<>
	struct convert<Vector3d>
	{
		static Node encode(const Vector3d& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		static bool decode(const Node& node, Vector3d& rhs)
		{
			if (!node.IsSequence() || node.size() != 3) 
			{
				return false;
			}

			rhs.x = node[0].as<double>();
			rhs.y = node[1].as<double>();
			rhs.z = node[2].as<double>();
			return true;
		}
	};
}


YamlFile::YamlFile()
{
}


YamlFile::~YamlFile()
{
}

bool YamlFile::LoadFile(const string& fileName)
{
	m_yamlData = YAML::LoadFile(fileName.c_str());

	//@TODO: add check for correct file load
	return true;
}

bool YamlFile::GetDataFromFile()
{
	if (!m_yamlData.IsSequence())
	{
		m_yamlData.reset();
		return false;
	}

	for (YAML::const_iterator it = m_yamlData.begin(); it != m_yamlData.end(); ++it)
	{
		if ((*it).IsMap())
		{
			m_data.push_back(DeseralizeYamlObject(*it));
		}
	}

	m_yamlData.reset();
	return true;
}

DeserializeData YamlFile::DeseralizeYamlObject(const YAML::Node data) const
{
	DeserializeData returnData;

	const std::string typeName = data[TYPE].as<std::string>();
	returnData.m_type = FindType(typeName);

	switch (returnData.m_type)
	{
	case WorldObject::WorldType::CT_Sphere:
		TokenizeSphere(data, returnData);
		break;
	case WorldObject::WorldType::CT_Point:
		TokenizePoint(data, returnData);
		break;
	case WorldObject::WorldType::CT_Camera:
		TokenizeCamera(data, returnData);
		break;
	case WorldObject::WorldType::CT_Image:
		TokenizeImage(data, returnData);
		break;
	default:
		returnData.m_type = WorldObject::WorldType::CT_Unknown;
		break;
	}

	return returnData;
}

WorldObject::WorldType YamlFile::FindType(const std::string& stringType) const
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

void YamlFile::TokenizeSphere(const YAML::Node data, DeserializeData& returnData) const
{
	returnData.m_mapVector[DeserializeData::POSITION] = data[POSITION].as<Vector3d>();
	returnData.m_mapDouble[DeserializeData::RADIUS] = data[RADIUS].as<double>();
}

void YamlFile::TokenizePoint(const YAML::Node data, DeserializeData& returnData) const
{
	returnData.m_mapVector[DeserializeData::POSITION] = data[POSITION].as<Vector3d>();
}

void YamlFile::TokenizeCamera(const YAML::Node data, DeserializeData& returnData) const
{
	returnData.m_mapVector[DeserializeData::POSITION] = data[POSITION].as<Vector3d>();
	returnData.m_mapVector[DeserializeData::DIRECTION] = data[DIRECTION].as<Vector3d>();

	returnData.m_mapVector[DeserializeData::PLANE1] = data["plane1"].as<Vector3d>();
	returnData.m_mapVector[DeserializeData::PLANE2] = data["plane2"].as<Vector3d>();
}

void YamlFile::TokenizeImage(const YAML::Node data, DeserializeData& returnData) const
{
	returnData.m_mapVector[DeserializeData::POSITION] = data[RESOLUTION].as<Vector3d>();
}

TEST(dataLoad, YamlFile)
{
	YamlFile test;
	ASSERT_TRUE(test.LoadFile("unittest.yaml"));
	ASSERT_TRUE(test.GetDataFromFile());
	const std::vector<DeserializeData>& result = test.GetData();

	EXPECT_EQ(result[0].m_type, WorldObject::WorldType::CT_Sphere);
	EXPECT_EQ(result[0].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(0, 1, 2));
	EXPECT_EQ(result[0].m_mapDouble.at(DeserializeData::MapIds::RADIUS), 2);

	EXPECT_EQ(result[1].m_type, WorldObject::WorldType::CT_Point);
	EXPECT_EQ(result[1].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(-1, -2, -3));

	EXPECT_EQ(result[2].m_type, WorldObject::WorldType::CT_Camera);
	EXPECT_EQ(result[2].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(1, 1, 1));
	EXPECT_EQ(result[2].m_mapVector.at(DeserializeData::MapIds::DIRECTION), Vector3d(1, 1, 1));

	EXPECT_EQ(result[3].m_type, WorldObject::WorldType::CT_Image);
	EXPECT_EQ(result[3].m_mapVector.at(DeserializeData::MapIds::POSITION), Vector3d(256, 640, 0));
}

/*TEST(FileLoadFail, YamlFile)
{
	YamlFile test;
	//ASSERT_FALSE(test.LoadFile("doesNotExist"));
}*/