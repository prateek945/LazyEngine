#pragma once
#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "../Includes/LazyIncludes.h"
#include "../Memory/MemoryManager.h"
#include "Colliders/ColliderBase.h"
#include "Algorithms/BasicCollisons.h"
#include <vector>
#include <memory>
namespace LE {
	typedef struct _Gravity {
		Primitives::Float32 magnitude;
		LEVector3 direction;
	}Gravity;
	class Physics {
		

	public:
		Primitives::Int16 *Collidables;
		Gravity gravity;
		std::vector<std::shared_ptr<Colliders::Collider>> objects[2];
		Physics(Primitives::Int16 objCount);
		void UpdateCollisions(Primitives::Int32);
		void ResolveCollisions(Primitives::Int32);
		
	};
};
#endif