#include "Physics.h"
namespace LE {
	Physics::Physics(Primitives::Int16 objCount) {
		Collidables = (Primitives::Int16*)calloc(objCount, sizeof(Primitives::Int16));

	}
	void Physics::UpdateCollisions(Primitives::Int32 framecount) {
		//objects[framecount % 2];
		Primitives::UInt16 currFrame = framecount % 2;
		Primitives::UInt16 prevFrame = !(currFrame);

		for (unsigned int i = 0; i < objects[prevFrame].size(); i++) {
			if(objects[currFrame].at(i)->metaData.bisMovable){
				objects[currFrame].at(i)->collidedObjs.clear();
				objects[prevFrame].at(i)->collidedObjs.clear();
				float curvel = objects[currFrame].at(i)->getMetaData().Velocity.m_x;
				float prevel = objects[prevFrame].at(i)->getMetaData().Velocity.m_x;
				objects[currFrame].at(i)->metaData.Velocity=(objects[prevFrame].at(i)->getMetaData().Velocity);

				for (unsigned int j = 0; j < objects[framecount % 2].size(); j++) {
					if (i == j) continue;
					if (objects[currFrame].at(i)->metaData.bhasMomentum) {
						LEVector3 normal = isColliding(objects[prevFrame].at(i).get(), objects[prevFrame].at(j).get());
						if (!(normal.m_x == 0.0f && normal.m_y == 0.0f && normal.m_z == 0.0f)) {
							objects[currFrame].at(i)->incrementCollisionCount();
							objects[currFrame].at(i)->addColliderIdNormal(j, normal);
						}
					}
				}
			}
		}
	}
	void Physics::ResolveCollisions(Primitives::Int32 framecount) {
		Primitives::UInt16 currFrame = framecount % 2;
		Primitives::UInt16 prevFrame = !(currFrame);
		Primitives::Float32 timedelta = 0.1;
		for (unsigned int i = 0; i < objects[currFrame].size(); i++) {
			if (objects[currFrame].at(i)->metaData.bisMovable) {
				LEVector3 newVelDir(0,0,0);
				LEVector3 velcpy = -objects[currFrame].at(i)->metaData.Velocity;
				velcpy.Normalize();
				LEVector3 normal(0, 0, 0);
				Primitives::Int16 objId;
				LEVector3 dP(0.0f, 0.0f, 0.0f);
				if (objects[currFrame].at(i)->metaData.bhasMomentum) {
					Primitives::UInt16 collisions =  objects[currFrame].at(i)->getCollidedObjs().size();
					for (unsigned int j = 0; j < objects[currFrame].at(i)->getCollidedObjs().size(); j++) {
						
						normal = objects[currFrame].at(i)->getColliderId(j).second;
						/*if (fabs(normal.dotProduct(velcpy)) < 0.1) {
							normal += velcpy;
							normal.Normalize();
						}*/
						objId = objects[currFrame].at(i)->getColliderId(j).first;
						newVelDir += 2.0f*normal.dotProduct(velcpy)*normal - (velcpy);

						//newVelDir -= (-objects[currFrame].at(i)->metaData.Velocity);
						newVelDir.Normalize();
						newVelDir += (objects[prevFrame].at(objId)->metaData.mass / objects[prevFrame].at(i)->metaData.mass)
							*(objects[prevFrame].at(objId)->metaData.Velocity);
						newVelDir.Normalize();
						objects[currFrame].at(i)->metaData.Velocity = (newVelDir);

					}
				}

				//objects[currFrame].at(i)->metaData.Energy *= 0.9f;
				if (objects[currFrame].at(i)->metaData.Energy > 0.25f) {
					if(objects[currFrame].at(i)->metaData.Gravity)
						objects[currFrame].at(i)->metaData.Velocity += (gravity.magnitude*timedelta)*gravity.direction;
					dP = timedelta*objects[currFrame].at(i)->metaData.Velocity;

				}
				
				objects[currFrame].at(i)->metaData.objMat.setTranslation(
					LEVector3(
						objects[prevFrame].at(i)->metaData.objMat.getTranslation() + dP
					)

				);
			}
			
		}
		
		
	}
};