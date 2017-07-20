#pragma once
#ifndef PHYSICS_MANAGER_H_
#define PHYSICS_MANAGER_H_
#include "../Includes/LazyIncludes.h"
#include "Physics.h"
namespace LE {
	class PhysicsManager {
	public:
		PhysicsManager();
		~PhysicsManager();
		void startUp(Primitives::Int16);
		void shutDown(void);
		Physics* get() const;
		static PhysicsManager* getInstance(void) { return gPhysicsManager; }
	private:
		static PhysicsManager *gPhysicsManager;
		Physics *m_singletonReference;

	};
};
#endif