#include "stdafx.h"
#include "Vector3d.h"
#include <gtest\gtest.h>
#include <math.h>
#include <float.h>
#include <iostream>
//#include "IRenderer.h"	//@TODO: Keep until we move materials to another class

using namespace std;

Vector3d::Vector3d()
:x(0)
,y(0)
,z(0)
{}

Vector3d::Vector3d(double inX, double inY, double inZ)
:x(inX)
, y(inY)
, z(inZ)
{}

Vector3d::Vector3d(const Vector3d& inVector)
:x(inVector.x)
, y(inVector.y)
, z(inVector.z)
{}

Vector3d::~Vector3d() {}


double Vector3d::length() const
{
	return std::sqrt(x*x + y*y + z*z);
}

double Vector3d::lengthSqr() const
{
	return (x*x + y*y + z*z);
}

Vector3d Vector3d::Normalize() const
{
	Vector3d returnVec;

	const double vlength = length();
	if (vlength == 0)
	{
		returnVec = (*this);
		return returnVec;
	}
	
	returnVec = (*this) / length();
	return returnVec;
}

void Vector3d::NormalizeVector()
{
	const double vlength = length();
	if (vlength == 0)
	{
		return;
	}

	(*this).operator/=(vlength);
}

double Vector3d::DotProduct(const Vector3d& rhs) const
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vector3d Vector3d::CrossProduct(const Vector3d& rhs) const
{
	Vector3d returnVector;
	returnVector.x = y*rhs.z - z*rhs.y;
	returnVector.y = z*rhs.x - x*rhs.z;
	returnVector.z = x*rhs.y - y*rhs.x;
	return returnVector;
}

bool Vector3d::operator != (const Vector3d& rhs) const
{
	bool returnValue;
	returnValue = !lpc::AlmostEqualRelative(x, rhs.x, DBL_EPSILON);
	returnValue |= !lpc::AlmostEqualRelative(y, rhs.y, DBL_EPSILON);
	returnValue |= !lpc::AlmostEqualRelative(z, rhs.z, DBL_EPSILON);
	return returnValue;
	//return x != rhs.x || y != rhs.y || z != rhs.z;
}

bool Vector3d::operator == (const Vector3d& rhs) const
{
	bool returnValue = true;
	returnValue &= lpc::AlmostEqualRelative(x, rhs.x, DBL_EPSILON);
	returnValue &= lpc::AlmostEqualRelative(y, rhs.y, DBL_EPSILON);
	returnValue &= lpc::AlmostEqualRelative(z, rhs.z, DBL_EPSILON);
	return returnValue;

	//return x == rhs.x && y == rhs.y && z == rhs.z;
}

Vector3d Vector3d::operator+(const Vector3d& rhs) const
{
	Vector3d returnVector;
	returnVector.x = x + rhs.x;
	returnVector.y = y + rhs.y;
	returnVector.z = z + rhs.z;
	return returnVector;
}

Vector3d Vector3d::operator-(const Vector3d& rhs) const
{
	Vector3d returnVector;
	returnVector.x = x - rhs.x;
	returnVector.y = y - rhs.y;
	returnVector.z = z - rhs.z;
	return returnVector;
}

Vector3d Vector3d::operator-() const
{
	Vector3d returnVector;
	returnVector.x = -x;
	returnVector.y = -y;
	returnVector.z = -z;
	return returnVector;
}

Vector3d Vector3d::operator*(const Vector3d& scale) const
{
	Vector3d returnVector;
	returnVector.x = x*scale.x;
	returnVector.y = y*scale.y;
	returnVector.z = z*scale.z;
	return returnVector;
}

void Vector3d::operator+=(const Vector3d& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

void Vector3d::operator-=(const Vector3d& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

Vector3d Vector3d::operator*(double scale) const
{
	Vector3d returnVec(x, y, z);
	returnVec *= scale;
	return returnVec;
}
Vector3d Vector3d::operator / (double scale) const
{
	Vector3d returnVec(x, y, z);
	returnVec /= scale;
	return returnVec;
}

void Vector3d::operator *= (double scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vector3d::operator /= (double scale)
{
	x /= scale;
	y /= scale;
	z /= scale;
}

RGBA Vector3d::ToRGBA() const
{
	return (static_cast<uint8_t>(x) << 24) + (static_cast<uint8_t>(y) << 16) + (static_cast<uint8_t>(z) << 8);
}

string Vector3d::ToString() const
{
	return to_string(x) + string(" ") + to_string(y) + string(" ") + to_string(z);
	
}

TEST(Length, Vector3d)
{
	Vector3d test(5, 2, 1);

	ASSERT_EQ(test.length(), 5.477225575051661);
}

TEST(LengthSqr, Vector3d)
{
	Vector3d test(5, 2, 1);

	ASSERT_EQ(test.lengthSqr(), 30);
}

TEST(Normalize, Vector3d)
{
	Vector3d test1(3, 4, 0), test2(1, 2, 0);
	Vector3d testResult = (test1 - test2).Normalize();
	Vector3d zeroLength = Vector3d(0, 0, 0).Normalize();	// protect against divide by zero

	EXPECT_EQ(testResult.x, 0.70710678118654746);
	EXPECT_EQ(testResult.y, 0.70710678118654746);
	EXPECT_EQ(testResult.z, 0);
	EXPECT_EQ(zeroLength, Vector3d(0, 0, 0));
}


TEST(NormalizeVector, Vector3d)
{
	Vector3d test1(3, 4, 0), test2(1, 2, 0);
	Vector3d testResult = (test1 - test2);
	Vector3d zeroLength = Vector3d(0, 0, 0);	// protect against divide by zero

	testResult.NormalizeVector();
	zeroLength.NormalizeVector();

	EXPECT_EQ(testResult.x, 0.70710678118654746);
	EXPECT_EQ(testResult.y, 0.70710678118654746);
	EXPECT_EQ(testResult.z, 0);
	EXPECT_EQ(zeroLength, Vector3d(0, 0, 0));
}

TEST(DotProduct, Vector3d)
{
	Vector3d One(1, 2, 3);
	Vector3d Two(4, -5, 6);

	EXPECT_EQ(One.DotProduct(Two), 12);
	EXPECT_EQ(Two.DotProduct(One), 12);
}

TEST(CrossProduct, Vector3d)
{
	Vector3d One(3, -3, 1);
	Vector3d Two(4, 9, 2);

	EXPECT_EQ(One.CrossProduct(Two), Vector3d(-15, -2, 39));
}

TEST(OperatorEquality, Vector3d)
{
	Vector3d one(1, 1, 1), two(1, 1, 1), three(2, 2, 2);

	EXPECT_TRUE(one == two);
	EXPECT_FALSE(one == three);

	EXPECT_TRUE(one != three);
	EXPECT_FALSE(one != two);
}

TEST(OperatorNonEquality, Vector3d)
{
	Vector3d one(1, 1, 1), two(1, 1, 1), three(2, 2, 2);

	EXPECT_FALSE(one != two);
	EXPECT_TRUE(one != three);
}

TEST(OperatorPlus, Vector3d)
{
	Vector3d one(1, 1, 1), two(2, 2, 2);

	Vector3d result = one + two;

	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 3);
	EXPECT_EQ(result.z, 3);
}

TEST(OperatorMinus, Vector3d)
{
	Vector3d one(1, 1, 1), two(2, 2, 2);

	Vector3d result = one - two;

	Vector3d three = Vector3d(1, 1, 1) - Vector3d(1, 1, 1);
	cout << three.ToString() << endl;

	EXPECT_EQ(result.x, -1);
	EXPECT_EQ(result.y, -1);
	EXPECT_EQ(result.z, -1);
}

TEST(OperatorPlusEqual, Vector3d)
{
	Vector3d one(1, 1, 1), two(2, 2, 2);

	one += two;

	EXPECT_EQ(one.x, 3);
	EXPECT_EQ(one.y, 3);
	EXPECT_EQ(one.z, 3);
}
TEST(OperatorMinusEqual, Vector3d)
{
	Vector3d one(1, 1, 1), two(2, 2, 2);

	one -= two;

	EXPECT_EQ(one.x, -1);
	EXPECT_EQ(one.y, -1);
	EXPECT_EQ(one.z, -1);
}
TEST(OperatorDiv, Vector3d)
{
	Vector3d test(3, 6, 9), result;
	result = test / 3;

	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 2);
	EXPECT_EQ(result.z, 3);
}
TEST(OperatorDivEquals, Vector3d)
{
	Vector3d test(3, 6, 9);
	test /= 3;

	EXPECT_EQ(test.x, 1);
	EXPECT_EQ(test.y, 2);
	EXPECT_EQ(test.z, 3);
}
TEST(OperatorMult, Vector3d)
{
	Vector3d test(1, 2, 3), result;
	result = test * 3;

	EXPECT_EQ(result.x, 3);
	EXPECT_EQ(result.y, 6);
	EXPECT_EQ(result.z, 9);
}
TEST(OperatorMultEquals, Vector3d)
{
	Vector3d test(1, 2, 3);
	test *= 3;

	EXPECT_EQ(test.x, 3);
	EXPECT_EQ(test.y, 6);
	EXPECT_EQ(test.z, 9);
}

TEST(ToString, Vector3d)
{
	Vector3d test(5, 2, 1);

	//EXPECT_TRUE
	EXPECT_EQ(test.ToString(), string("5.000000 2.000000 1.000000"));
}