#pragma once
#ifndef MATHHELPERS_H_
#define MATHHELPERS_H_

#include "../Primitives/Primitives.h"
#include <math.h>

inline bool compareFloats(const Primitives::Float32 &f0, const Primitives::Float32 &f1)
{
	return (fabs(f0 - f1) < Primitives::Constants::c_Epsilon_F32);
}
template <typename T>
T max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template <typename T>
T min(const T& a, const T& b)
{
	return a < b ? a : b;
}
#endif