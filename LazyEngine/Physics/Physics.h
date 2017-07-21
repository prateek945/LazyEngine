#pragma once
#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "../Includes/LazyIncludes.h"
#include "../Memory/MemoryManager.h"
#include "../Physics/Colliders/Frustrum.h"
#include "../Physics/Colliders/Cube.h"
#include "../Physics/Colliders/Sphere.h"
namespace LE {
	class Physics {
		Primitives::Int16 *Collidables;
	public:
		Physics(Primitives::Int16 objCount);
		
	};
};
#endif