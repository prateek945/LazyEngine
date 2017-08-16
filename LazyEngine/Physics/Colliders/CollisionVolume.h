#pragma once
#ifndef COLLISION_VOLUME_H_
#define COLLISION_VOLUME_H_
#include "../PrimitiveShapes/Plane.h"
#include "../../Includes/LazyIncludes.h"
#include "ColliderBase.h"

namespace LE {
	namespace Colliders {
	
		class CollisionVolume : public Collider{
			//ColliderMeta metaData;
			PrimitiveShapes::Point *vertexData;
			Primitives::Int16 *indexData;
			Primitives::Int16 vertexCount;

		public:
			
			CollisionVolume(PrimitiveShapes::Point *vertexData,
				Primitives::Int16 *indexData, Primitives::Int16 vertexCount,ColliderMeta metaData):Collider(metaData),vertexCount(vertexCount) {
				setColliderType(ColliderType::TypeCollisionVolume);
				this->vertexData = (PrimitiveShapes::Point*)calloc(vertexCount, sizeof(PrimitiveShapes::Point));
				this->indexData = (Primitives::Int16*)calloc(vertexCount, sizeof(Primitives::Int16));
				memcpy(this->vertexData, vertexData, vertexCount * sizeof(PrimitiveShapes::Point));
				memcpy(this->indexData, indexData, vertexCount * sizeof(Primitives::Int16));
				
			}
			PrimitiveShapes::Point getFurthestInDir(LEVector3 *Dir) override {
				Primitives::Float32 maxDist = 0.f;
				for (int i = 0; i < vertexCount; i++) {
					
				}
			}
		};
	};
};
#endif


