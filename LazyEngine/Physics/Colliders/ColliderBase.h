#pragma once
#ifndef COLLIDER_BASE_H_
#define COLLIDER_BASE_H_
#include "../PrimitiveShapes/Point.h"
#include "ColliderMeta.h"
#include <vector>
namespace LE {
	namespace Colliders {
		
		class Collider {
			
			Primitives::Int16 collisionCount;
			std::vector<Primitives::Int16> collidedObjs;
			
		public:
			ColliderMeta metaData;
			Collider();
			Collider(ColliderMeta m);
			Collider(Collider &&) = default;
			Collider(Collider const&col);
			virtual PrimitiveShapes::Point getFurthestInDir(LEVector3 *Dir) = 0;
			ColliderMeta getMetaData();
			void setColliderType(ColliderType type);
			void setCollisionCount(Primitives::Int16 count);
			 Primitives::Int16 getCollisionCount()const;
			void incrementCollisionCount();
			void addColliderId(Primitives::Int16 index);
			Primitives::Int16 getColliderId(Primitives::Int16 index)const;
			std::vector<Primitives::Int16> getCollidedObjs()const;
			
		};
	};
};
#endif
