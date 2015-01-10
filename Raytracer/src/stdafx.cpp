// stdafx.cpp : source file that includes just the standard includes
// Raytracer.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//using namespace lpc;

bool lpc::AlmostEqualRelative(double A, double B, double maxRelDiff)
{
	// Calculate the difference.
	const double diff = fabs(A - B);
	A = fabs(A);
	B = fabs(B);
	// Find the largest
	const double largest = (B > A) ? B : A;

	return (diff <= largest * maxRelDiff);
}
