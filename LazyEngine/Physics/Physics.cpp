#include "Physics.h"
namespace LE {
	Physics::Physics(Primitives::Int16 objCount) {
		Collidables = (Primitives::Int16*)MemoryManager::getInstance()->get()->getStackAllocator()->Alloc(objCount*sizeof(Primitives::Int16*));

	}
};