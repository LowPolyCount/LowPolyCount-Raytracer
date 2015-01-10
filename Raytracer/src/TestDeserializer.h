#pragma once
#include "Deserializer.h"

class TestDeserializer :
	public Deserializer
{
	friend class Deserializer;
public:
	TestDeserializer();
	virtual ~TestDeserializer();
	DeserializeData TestDeseralizeLine(const std::string& line) const;
	WorldObject::WorldType TestFindType(const std::string& stringType) const;
	void TestTokenizeSphere(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	void TestTokenizePoint(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	void TestTokenizeCamera(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
	void TestTokenizeImage(const std::string& line, const size_t dataStart, DeserializeData& returnData) const;
};

