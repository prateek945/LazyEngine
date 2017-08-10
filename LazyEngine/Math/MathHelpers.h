#pragma once
#ifndef MATHHELPERS_H_
#define MATHHELPERS_H_


#include "../Includes/LazyIncludes.h"
#include <math.h>

namespace LE{
	
	
	inline bool compareVals(const Primitives::Float32 &f0, const Primitives::Float32 &f1)
	{
		return (fabs(f0 - f1) < Primitives::Constants::c_Epsilon_F32);
	}
	
	
};
#endif