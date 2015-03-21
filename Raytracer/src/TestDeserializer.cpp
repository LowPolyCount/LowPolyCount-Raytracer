#include "stdafx.h"
#include "TestDeserializer.h"
#include "gtest\gtest.h"
#include "DeserializeData.h"
#include "CollidableObject.h"
#include <iostream>

using namespace std;


TestDeserializer::TestDeserializer()
{
}


TestDeserializer::~TestDeserializer()
{
}

DeserializeData TestDeserializer::TestDeseralizeLine(const std::string& line) const
{
	return Deserializer::DeseralizeLine(line);
}

Object::ObjectType TestDeserializer::TestFindType(const std::string& stringType) const
{
	return Deserializer::FindType(stringType);
}

void TestDeserializer::TestTokenizeSphere(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	Deserializer::TokenizeSphere(line, dataStart, returnData);
}

void TestDeserializer::TestTokenizePoint(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	Deserializer::TokenizePoint(line, dataStart, returnData);
}

void TestDeserializer::TestTokenizeCamera(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	Deserializer::TokenizeCamera(line, dataStart, returnData);
}

void TestDeserializer::TestTokenizeImage(const std::string& line, const size_t dataStart, DeserializeData& returnData) const
{
	Deserializer::TokenizeImage(line, dataStart, returnData);
}

/*const char* TEST_SPHERE = "sphere 0.0 0 0 5";
const char* TEST_POINT = "point 0 1 2";
const char* TEST_CAMERA = "camera 1 2 3 1 2 3";
const char* TEST_IMAGE = "image 640 480";

TEST(TestFindType, TestDeserializer)
{
	const char* TEST_SPHERE = "sphere";
	const char* TEST_POINT = "point";
	const char* TEST_CAMERA = "camera";
	const char* TEST_IMAGE = "image";

	TestDeserializer test;
	WorldObject::WorldType testSphere = test.TestFindType(TEST_SPHERE);
	WorldObject::WorldType testPoint = test.TestFindType(TEST_POINT);
	WorldObject::WorldType testCamera = test.TestFindType(TEST_CAMERA);
	WorldObject::WorldType testImage = test.TestFindType(TEST_IMAGE);
	WorldObject::WorldType testUnknown = test.TestFindType("sdfsdfsadfndf");

	EXPECT_EQ(testSphere, WorldObject::WorldType::CT_Sphere);
	EXPECT_EQ(testPoint, WorldObject::WorldType::CT_Point);
	EXPECT_EQ(testCamera, WorldObject::WorldType::CT_Camera);
	EXPECT_EQ(testImage, WorldObject::WorldType::CT_Image);
	EXPECT_EQ(testUnknown, WorldObject::WorldType::CT_Unknown);
}

TEST(TestTokenizeSphere, TestDeserializer)
{
	TestDeserializer test;
	DeserializeData testData;
	test.TestTokenizeSphere(TEST_SPHERE, 6, testData);

	EXPECT_EQ(testData.m_mapVector[DeserializeData::POSITION], Vector3d(0, 0, 0));
	EXPECT_EQ(testData.m_mapDouble[DeserializeData::RADIUS], 5);
}


TEST(TestTokenizePoint, TestDeserializer)
{
	TestDeserializer test;
	DeserializeData testData;
	test.TestTokenizePoint(TEST_POINT, 5, testData);

	EXPECT_EQ(testData.m_mapVector[DeserializeData::POSITION], Vector3d(0, 1, 2));
}


TEST(TestTokenizeCamera, TestDeserializer)
{
	TestDeserializer test;
	DeserializeData testData;
	test.TestTokenizeCamera(TEST_CAMERA, 6, testData);

	EXPECT_EQ(testData.m_mapVector[DeserializeData::POSITION], Vector3d(1, 2, 3));
	EXPECT_EQ(testData.m_mapVector[DeserializeData::DIRECTION], Vector3d(1, 2, 3));
}


TEST(TestTokenizeImage, TestDeserializer)
{
	TestDeserializer test;
	DeserializeData testData;
	test.TestTokenizeImage(TEST_IMAGE, 5, testData);

	EXPECT_EQ(testData.m_mapVector[DeserializeData::POSITION], Vector3d(640, 480, 0));
}

TEST(TestLineBuild, TestDeserializer)
{
	TestDeserializer test;
	DeserializeData testSphere = test.TestDeseralizeLine(TEST_SPHERE);
	DeserializeData testPoint = test.TestDeseralizeLine(TEST_POINT);
	DeserializeData testCamera = test.TestDeseralizeLine(TEST_CAMERA);
	DeserializeData testImage = test.TestDeseralizeLine(TEST_IMAGE);

	EXPECT_EQ(testSphere.m_type, WorldObject::WorldType::CT_Sphere);
	EXPECT_EQ(testPoint.m_type, WorldObject::WorldType::CT_Point);
	EXPECT_EQ(testCamera.m_type, WorldObject::WorldType::CT_Camera);
	EXPECT_EQ(testImage.m_type, WorldObject::WorldType::CT_Image);

	EXPECT_EQ(testSphere.m_mapVector[DeserializeData::POSITION], Vector3d(0, 0, 0));
	EXPECT_EQ(testPoint.m_mapVector[DeserializeData::POSITION], Vector3d(0, 1, 2));
	EXPECT_EQ(testCamera.m_mapVector[DeserializeData::POSITION], Vector3d(1, 2, 3));
	EXPECT_EQ(testImage.m_mapVector[DeserializeData::POSITION], Vector3d(640, 480, 0));

	EXPECT_EQ(testSphere.m_mapDouble[DeserializeData::RADIUS], 5);
}*/