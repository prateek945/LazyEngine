#pragma once
#ifndef COLLIDER_BASE_H_
#define COLLIDER_BASE_H_
#include "../PrimitiveShapes/Point.h"
#include "ColliderMeta.h"
#include <vector>
namespace LE {
	namespace Colliders {
		
		class Collider {
	
		public:
			std::vector<std::pair<Primitives::Int16,LEVector3>> collidedObjs;
			Primitives::Int16 collisionCount;
			ColliderMeta metaData;
			Collider();
			Collider(ColliderMeta m);
			Collider(Collider &&) = default;
			Collider(Collider const&col);
			virtual void generateValuesFromBuffer(vector<Primitives::Float32>) = 0;
			virtual PrimitiveShapes::Point getFurthestInDir(LEVector3 *Dir) = 0;
			ColliderMeta getMetaData();
			void setColliderType(ColliderType type);
			void setCollisionCount(Primitives::Int16 count);
			 Primitives::Int16 getCollisionCount()const;
			void incrementCollisionCount();
			void addColliderIdNormal(Primitives::Int16 id,LEVector3 normal);
			std::pair<Primitives::Int16, LEVector3> getColliderId(Primitives::Int16 index)const;
			std::vector<std::pair<Primitives::Int16, LEVector3>> getCollidedObjs()const;
			
		};
	};
};
#endif
