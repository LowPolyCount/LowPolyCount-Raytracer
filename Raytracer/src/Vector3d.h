#pragma once
#include <string>

class Vector3d
{
public:
	Vector3d();
	Vector3d(double inX, double inY, double inZ);
	Vector3d(const Vector3d& inVector);
	~Vector3d();
	double length() const;
	double lengthSqr() const;
	Vector3d Normalize() const;
	void NormalizeVector();
	double DotProduct(const Vector3d& rhs) const;
	Vector3d CrossProduct(const Vector3d& rhs) const;

	bool operator==(const Vector3d& rhs) const;
	bool operator!=(const Vector3d& rhs) const;
	Vector3d operator+(const Vector3d& rhs) const;
	Vector3d operator-(const Vector3d& rhs) const;
	Vector3d operator*(double scale) const;
	Vector3d operator/(double scale) const;
	void operator+=(const Vector3d& rhs);
	void operator-=(const Vector3d& rhs);
	void operator*=(double scale);
	void operator/=(double scale);
	std::string ToString() const;

	double x, y, z;
};

