#pragma once
#ifndef COLLISION_VOLUME_H_
#define COLLISION_VOLUME_H_
#include "../PrimitiveShapes/Point.h"
#include "../PrimitiveShapes/Plane.h"
#include "../../Includes/LazyIncludes.h"
#include "ColliderMeta.h"
namespace LE {
	namespace Colliders {
		//The class holds a set of points to be read in counter clockwise order.
		//Second implementation can hold both vertex Data as well as index buffer.
		class CollisionVolume {
			ColliderMeta metaData;
			PrimitiveShapes::Point<> *vertexData;
			Primitives::Int16 *indexData;

		public:
			
			CollisionVolume(PrimitiveShapes::Point<> *vertexData,
				Primitives::Int16 *indexData, Primitives::Int16 vertexCount) {
				this->vertexData = (PrimitiveShapes::Point<>*)calloc(vertexCount, sizeof(PrimitiveShapes::Point<>));
				this->indexData = (Primitives::Int16*)calloc(vertexCount, sizeof(Primitives::Int16));
				memcpy(this->vertexData, vertexData, vertexCount * sizeof(PrimitiveShapes::Point<>));
				memcpy(this->indexData, indexData, vertexCount * sizeof(Primitives::Int16));
				this->metaData.type = ColliderType::CollisionVolume;
			}
		};
	};
};
#endif


