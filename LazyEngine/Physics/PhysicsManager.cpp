#include "PhysicsManager.h"

namespace LE {
	PhysicsManager::PhysicsManager() {}
	PhysicsManager::~PhysicsManager() {}

	void PhysicsManager::startUp() {
		m_singletonReference = new Physics();		
	}
	void PhysicsManager::shutDown() {
		delete m_singletonReference;
	}
	Physics* PhysicsManager::get() const{
		return m_singletonReference;
	}
};