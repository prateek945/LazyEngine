#include "PhysicsManager.h"

namespace LE {
	PhysicsManager* PhysicsManager::gPhysicsManager = new PhysicsManager();
	PhysicsManager::PhysicsManager() {}
	PhysicsManager::~PhysicsManager() {}

	void PhysicsManager::startUp(Primitives::Int16 collidables) {
		m_singletonReference = new Physics(collidables);		
	}
	void PhysicsManager::shutDown() {
		delete m_singletonReference;
	}
	Physics* PhysicsManager::get() const{
		return m_singletonReference;
	}
	PhysicsManager* PhysicsManager::getInstance() { return PhysicsManager::gPhysicsManager; }
};