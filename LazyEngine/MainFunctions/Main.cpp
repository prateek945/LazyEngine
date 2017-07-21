#include "Main.h"
#include <time.h>


namespace LE {
	int MainWrapper() {
		cout << "Hello\n";

		LogManager *gLogManager = LogManager::getInstance();
		gLogManager->startUp();
		LAZYASSERT(gLogManager->get(), "Log Manager Not Set")
			
		MemoryManager *gMemoryManager = MemoryManager::getInstance();
		gMemoryManager->startUp();
		LAZYASSERT(gMemoryManager->get(), "Memory Manager Not Set")

		PhysicsManager *gPhysicsManager = PhysicsManager::getInstance();
		gPhysicsManager->startUp((Primitives::Int16) 100);
		LAZYASSERT(gPhysicsManager->get(),"Physics Manager Not Set")

		Colliders::Frustrum<> viewFrust = Colliders::Frustrum<>(PrimitiveShapes::Point<>(), LEVector3<>(1.f, 0.f, 0.f),LEVector3<>(0.f,1.f,0.f), 60.f, 10.f, 100.f);
		
		
		return 0;
	}
};

using namespace std;
//int main(int argc, char* argv) {
//
//	LE::MainWrapper();
//}
