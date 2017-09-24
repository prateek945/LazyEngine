#pragma once
#ifndef LIGHT_OBJECT_H_
#define LIGHT_OBJECT_H_
#include "../Includes/LazyIncludes.h"
#include "../Math/LEVector.h"
namespace LE {
	enum LightType {
		Directional = 0,
		Point,
		Spot
	};
	class LightObject {
	public:
		LEVector3 position;
		LEVector3 direction;
		LEVector3 color;
		Primitives::Float32 spec;
		LightType type;
	};
};
#endif
