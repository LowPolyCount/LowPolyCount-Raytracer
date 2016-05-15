#pragma once
#include <string>
#include "RaytracerTypes.h"

class Vector3d
{
public:
	static const uint8_t MAX_COLORVALUE = 255;

	Vector3d();
	Vector3d(double inX, double inY, double inZ);
	Vector3d(const Vector3d& inVector);
	virtual ~Vector3d();
	double length() const;
	double lengthSqr() const;
	//Vector3d Normalize() const;
	void NormalizeVector();
	double DotProduct(const Vector3d& rhs) const;
	Vector3d CrossProduct(const Vector3d& rhs) const;

	bool operator==(const Vector3d& rhs) const;
	bool operator!=(const Vector3d& rhs) const;
	Vector3d operator-() const;
	Vector3d operator-(const Vector3d& rhs) const;
	Vector3d operator+(const Vector3d& rhs) const;
	Vector3d operator*(const Vector3d& scale) const;
	Vector3d operator*(double scale) const;
	Vector3d operator/(double scale) const;
	void operator+=(const Vector3d& rhs);
	void operator-=(const Vector3d& rhs);
	void operator*=(double scale);
	void operator/=(double scale);
	
	//@todo: consider moving these into it's own colorvector class or some such.
	void NormalizeColorValues();
	RGBA ToRGBA() const;

	std::string ToString() const;

	double x, y, z;
};

