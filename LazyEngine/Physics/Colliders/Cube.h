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
			void generateValuesFromBuffer(vector<Primitives::Float32> vertices) override 
			{
				Primitives::Float32 min_x = Primitives::Constants::c_MaxFloat32;
				Primitives::Float32 max_x = 0.f;
				Primitives::Float32 min_y = Primitives::Constants::c_MaxFloat32;
				Primitives::Float32 max_y = 0.f;
				Primitives::Float32 min_z = Primitives::Constants::c_MaxFloat32;
				Primitives::Float32 max_z = 0.f;
				for (unsigned int i = 0; i < vertices.size()/3; i++) {
					if (vertices.at(3 * i) > max_x) max_x = vertices.at(3 * i);
					if (vertices.at(3 * i) < min_x) min_x = vertices.at(3 * i);
					if (vertices.at(3 * i + 1) > max_y) max_y = vertices.at(3 * i + 1);
					if (vertices.at(3 * i + 1) < min_y) min_y = vertices.at(3 * i + 1);
					if (vertices.at(3 * i + 2) > max_z) max_z = vertices.at(3 * i + 2);
					if (vertices.at(3 * i + 2) < min_z) min_z = vertices.at(3 * i + 2);
				}
				min.x = min_x;
				min.y = min_y;
				min.z = min_z;
				max.x = max_x;
				max.y = max_y;
				max.z = max_z;
			}
			
		};



	};
};
#endif // !CUBE_H_

