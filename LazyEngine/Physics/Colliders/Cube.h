#pragma once
#ifndef CUBE_H_
#define CUBE_H_

#include "../../Includes/LazyIncludes.h"
#include "ColliderMeta.h"
#include "../PrimitiveShapes/Point.h"
#include "../PrimitiveShapes/Plane.h"
namespace LE {
	namespace Colliders {
		class Cube {
			ColliderMeta metaData;
			PrimitiveShapes::Point<> min, max,center;
		public :
			//Unit cube centered at <0,0,0>
			Cube();
			//Center min and max.
			Cube(PrimitiveShapes::Point<>, PrimitiveShapes::Point<>, PrimitiveShapes::Point<>);
			//Center, length, breadth,height
			Cube(PrimitiveShapes::Point<>, Primitives::Float32, Primitives::Float32,Primitives::Float32);
			//Center <0,0,0> length,breadth,height
			Cube(Primitives::Float32, Primitives::Float32, Primitives::Float32);
		
			//get Meta Data
			ColliderMeta getMetaData() { return metaData; }
		};

		Cube::Cube() {
			this->center = PrimitiveShapes::Point<>(0.f, 0.f, 0.f);
			this->min = PrimitiveShapes::Point<>(-1.f, -1.f, -1.f);
			this->max = PrimitiveShapes::Point<>(1.f, 1.f, 1.f);
			this->metaData.type = ColliderType::Cube;
		}

		Cube::Cube(PrimitiveShapes::Point<> center, PrimitiveShapes::Point<> min, PrimitiveShapes::Point<> max) {
			this->center = center;
			this->min = min;
			this->max = max;
			this->metaData.type = ColliderType::Cube;
		}

		Cube::Cube(PrimitiveShapes::Point<> center, Primitives::Float32 length, Primitives::Float32 breadth,Primitives::Float32 height) {
			this->center = center;
			this->min = PrimitiveShapes::Point<>(center.x - breadth * 0.5f,center.y - height *0.5f,center.z - length * 0.5f);
			this->max = PrimitiveShapes::Point<>(center.x + breadth * 0.5f, center.y + height *0.5f, center.z + length * 0.5f);
			this->metaData.type = ColliderType::Cube;
		}

		Cube::Cube(Primitives::Float32 length, Primitives::Float32 breadth, Primitives::Float32 height) {
			this->center = PrimitiveShapes::Point<>(0.f, 0.f, 0.f);
			this->min = PrimitiveShapes::Point<>(center.x - breadth * 0.5f, center.y - height *0.5f, center.z - length * 0.5f);
			this->max = PrimitiveShapes::Point<>(center.x + breadth * 0.5f, center.y + height *0.5f, center.z + length * 0.5f);
			this->metaData.type = ColliderType::Cube;
		}


	};
};
#endif // !CUBE_H_

