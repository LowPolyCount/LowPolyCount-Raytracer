// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


// TODO: reference additional headers your program requires here
#include <gtest\gtest.h>
#include <iostream>

 
namespace lpc
{
	bool AlmostEqualRelative(double A, double B, double maxRelDiff);
}