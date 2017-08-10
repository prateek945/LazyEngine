#pragma once
#ifndef CUBE_H_
#define CUBE_H_


#include "ColliderBase.h"

namespace LE {
	namespace Colliders {
		class Cube : public Collider {
			
		public :
			union {
				struct {
					PrimitiveShapes::Point min, max, center;
				};
				PrimitiveShapes::Point points[3];
			};
			//Unit cube centered at <0,0,0>
			Cube(ColliderMeta meta) : Collider(meta) {
				center = PrimitiveShapes::Point(meta.objMat.m30, meta.objMat.m31, meta.objMat.m32);
				min = PrimitiveShapes::Point(-1.f, -1.f, -1.f);
				max = PrimitiveShapes::Point(1.f, 1.f, 1.f);
				setColliderType(ColliderType::TypeCube);
				
			}
			//Center min and max.
			Cube(PrimitiveShapes::Point c, PrimitiveShapes::Point mi, PrimitiveShapes::Point ma, ColliderMeta meta) : Collider(meta){
				center = c;
				min = mi;
				max = ma;
				setColliderType(ColliderType::TypeCube);
			}
			//Center, length, breadth,height
			Cube(PrimitiveShapes::Point c, Primitives::Float32 length, Primitives::Float32 breadth, Primitives::Float32 height, ColliderMeta meta) : Collider(meta){
				center = c;
				min = PrimitiveShapes::Point(center.x - breadth * 0.5f, center.y - height *0.5f, center.z - length * 0.5f);
				max = PrimitiveShapes::Point(center.x + breadth * 0.5f, center.y + height *0.5f, center.z + length * 0.5f);
				setColliderType(ColliderType::TypeCube);
			}
			//Center <0,0,0> length,breadth,height
			Cube(Primitives::Float32 length, Primitives::Float32 breadth, Primitives::Float32 height, ColliderMeta meta) : Collider(meta) {
				center = PrimitiveShapes::Point(meta.objMat.m30, meta.objMat.m31, meta.objMat.m32);
				min = PrimitiveShapes::Point(center.x - breadth * 0.5f, center.y - height *0.5f, center.z - length * 0.5f);
				max = PrimitiveShapes::Point(center.x + breadth * 0.5f, center.y + height *0.5f, center.z + length * 0.5f);
				setColliderType(ColliderType::TypeCube);
				
			}

			PrimitiveShapes::Point getFurthestInDir(LEVector3 *Dir) override
			{

				//LEVector3 point();
				LEVector3 localDir = *Dir * getMetaData().objMat;
				Primitives::Float32 l, b, h;
				b =( max.x >= min.x)?(max.x - min.x) / 2.0f : -(max.x - min.x) / 2.0f;
				h =(max.y >= min.y) ? (max.y - min.y) / 2.0f : -(max.y - min.y) / 2.0f;
				l = (max.z >= min.z)? (max.z - min.z) / 2.0f : -(max.z - min.z) / 2.0f;
				
				return (PrimitiveShapes::Point(LEVector3(localDir.m_x*b,localDir.m_y*h,localDir.m_z*l)));

			}
			
		};



	};
};
#endif // !CUBE_H_

