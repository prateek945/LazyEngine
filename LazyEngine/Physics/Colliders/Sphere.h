#pragma once
#ifndef SPHERE_H_
#define SPHERE_H_

#include "../../Includes/LazyIncludes.h"
#include "../PrimitiveShapes/Point.h"
#include "../PrimitiveShapes/Ray.h"
#include "ColliderMeta.h"
namespace LE {
	namespace Colliders {
		class Sphere {
			ColliderMeta metaData;
			PrimitiveShapes::Point<> center;
			Primitives::Float32 radius;
		public:
			//unit sphere
			Sphere():center(PrimitiveShapes::Point<>()),radius(1.f) {
				metaData.type = ColliderType::Sphere;
			}
			Sphere(PrimitiveShapes::Point<> c,Primitives::Float32 r): center(c),radius(r) {
				metaData.type = ColliderType::Sphere;
			}
			Sphere(Primitives::Float32 r):center(PrimitiveShapes::Point<>()),radius(r) {
				metaData.type = ColliderType::Sphere;
			}

			ColliderMeta getMetaData() { return metaData; }
			void setMetaData(ColliderMeta metaData) { this->metaData = metaData; }
			
		};
	};
};
#endif

