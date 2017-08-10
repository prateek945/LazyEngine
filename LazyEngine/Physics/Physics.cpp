#include "Physics.h"
namespace LE {
	Physics::Physics(Primitives::Int16 objCount) {
		Collidables = (Primitives::Int16*)calloc(objCount,sizeof(Primitives::Int16));

	}
	void Physics::UpdateCollisions(Primitives::Int32 framecount) {
		//objects[framecount % 2];
		Primitives::UInt16 currFrame = framecount % 2;
		Primitives::UInt16 prevFrame = !(currFrame);
		for (unsigned int i = 0; i < objects[prevFrame].size(); i++) {
			objects[currFrame].at(i)->setCollisionCount(0);
			for (unsigned int j = 0; j < objects[framecount % 2].size(); j++) {
				if (i == j) continue;
				if (isColliding(objects[prevFrame].at(i).get(), objects[prevFrame].at(j).get())) {
					objects[currFrame].at(i)->incrementCollisionCount();
					objects[currFrame].at(i)->addColliderId(j);
				}
			}
		}

	}
	void Physics::ResolveCollisions(Primitives::Int32 framecount) {
		Primitives::UInt16 currFrame = framecount % 2;
		
		for (unsigned int i = 0; i < objects[currFrame].size(); i++) {
			LEVector3 nextDelta = objects[currFrame].at(i)->metaData.velocityMagnitude*objects[currFrame].at(i)->metaData.velocityDir;
			nextDelta += ((gravity.magnitude*(0.1))*gravity.direction);
			objects[currFrame].at(i)->metaData.objMat.setTranslation(
				LEVector3(
					objects[currFrame].at(i)->metaData.objMat.getTranslation() + nextDelta
				)

			);
		}
	}
};