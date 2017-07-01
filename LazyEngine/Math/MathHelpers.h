#pragma once
#ifndef MATHHELPERS_H_
#define MATHHELPERS_H_


#include "../Includes/LazyIncludes.h"
#include <math.h>

namespace LE{
	
	template <typename T>
	inline bool compareVals(const T &f0, const T &f1)
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
};
#endif