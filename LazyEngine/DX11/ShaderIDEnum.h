#pragma once
#include "../Includes/LazyIncludes.h"

namespace LE {
	enum ShaderID : Primitives::Int16 {
		StandardShader = 0,
		DetialedShader,
		LightPass,
		EndOfList
	};
};