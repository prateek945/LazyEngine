#pragma once
#ifndef SPHERE_H_
#define SPHERE_H_


#include "ColliderBase.h"
namespace LE {
	namespace Colliders {
		class Sphere : public Collider{
			
			PrimitiveShapes::Point center;
			Primitives::Float32 radius;
		public:
			//unit sphere
			Sphere(ColliderMeta meta):radius(1.f),Collider(meta) {
				center = PrimitiveShapes::Point(meta.objMat.m30, meta.objMat.m31, meta.objMat.m32);
				setColliderType(ColliderType::TypeSphere);
			}
			Sphere(PrimitiveShapes::Point c,Primitives::Float32 r,ColliderMeta meta): center(c),radius(r), Collider(meta) {
				setColliderType(ColliderType::TypeSphere);
			}
			Sphere(Primitives::Float32 r,ColliderMeta meta):center(PrimitiveShapes::Point()),radius(r), Collider(meta) {
				setColliderType(ColliderType::TypeSphere);
			}
			PrimitiveShapes::Point getFurthestInDir(LEVector3 *Dir) override {
				ColliderMeta meta = getMetaData();
				LEVector3 localDir = *Dir * meta.objMat.inverse();
				return PrimitiveShapes::Point((LEVector3(center.x, center.y, center.z) + radius * (localDir)));
				
			}
			PrimitiveShapes::Point getCenter() { return center; }
			Primitives::Float32 getRadius() { return radius; }
			
		};
	};
};
#endif

