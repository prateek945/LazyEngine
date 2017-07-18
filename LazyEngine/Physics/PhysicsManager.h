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
		void startUp(void);
		void shutDown(void);
		Physics* get() const;
	private:
		static PhysicsManager *gPhysicsManager;
		Physics *m_singletonReference;

	};
};
#endif