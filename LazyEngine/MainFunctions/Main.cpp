#include "Main.h"

#include "../Physics/Algorithms/BasicCollisons.h"
#include <time.h>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;
namespace LE {
	int MainWrapper() {
		cout << "Hello\n";

		LogManager *gLogManager = LogManager::getInstance();
		gLogManager->startUp();
		LAZYASSERT(gLogManager->get(), "Log Manager Not Set")
			
		MemoryManager *gMemoryManager = MemoryManager::getInstance();
		gMemoryManager->startUp();
		
		PhysicsManager *gPhysicsManager = PhysicsManager::getInstance();
		gPhysicsManager->startUp((Primitives::Int16) 100);

		LAZYASSERT(gPhysicsManager->get(), "Physics Manager Not Set")

		EffectManager *gEffectManager = EffectManager::getInstance();
		gEffectManager->startUp();
		
		
		
		return 0;
	}
};

