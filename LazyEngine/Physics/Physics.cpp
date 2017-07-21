#include "Physics.h"
namespace LE {
	Physics::Physics(Primitives::Int16 objCount) {
		Collidables = (Primitives::Int16*)calloc(objCount,sizeof(Primitives::Int16));

	}
};