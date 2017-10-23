#pragma once
#ifndef FRUSTRUM_H_
#define FRUSTRUM_H_

#include "ColliderBase.h"
#include "../PrimitiveShapes/Plane.h"

namespace LE {
	namespace Colliders {
		
		class Frustrum : public Collider {
			
			
		public:
			union {
				struct
				{
					PrimitiveShapes::Plane nearPlane, farPlane, leftPlane, rightPlane, topPlane, bottomPlane;
				};
				PrimitiveShapes::Plane Planes[6];
			};
			//NOTE : Plane normales are defined to be inwards for all 6 planes.
			//NOTE : Z Axis is forward axis WOrld space or otherwise.

			//Generating planes from FOV (in degrees), origin, near and far clip distances.
			Frustrum() :Collider(ColliderMeta{}) {
				nearPlane = PrimitiveShapes::Plane();
				farPlane = PrimitiveShapes::Plane();
				leftPlane = PrimitiveShapes::Plane();
				rightPlane = PrimitiveShapes::Plane();
				topPlane = PrimitiveShapes::Plane();
				bottomPlane = PrimitiveShapes::Plane();
			};
			Frustrum(ColliderMeta& meta) : Collider(meta){ 
				nearPlane = PrimitiveShapes::Plane();
				farPlane = PrimitiveShapes::Plane();
				leftPlane = PrimitiveShapes::Plane();
				rightPlane = PrimitiveShapes::Plane();
				topPlane = PrimitiveShapes::Plane();
				bottomPlane = PrimitiveShapes::Plane();
				setColliderType(ColliderType::TypeFrustrum); }

			Frustrum(PrimitiveShapes::Point& origin, LEVector3 axis, LEVector3 up, const Primitives::Float32 FOV, const Primitives::Float32 nearDist, const Primitives::Float32 farDist,ColliderMeta meta) : Collider(meta) {
				//Setup Near and Far clip planes first.
				setColliderType(ColliderType::TypeFrustrum);
				Primitives::Float32 theta = DEGTORAD(FOV) / 2.f;
				//near plane
				axis.Normalize();
				up.Normalize();
				nearPlane.setPoint(PrimitiveShapes::Point(origin.x + axis.m_x * nearDist, origin.y + axis.m_y * nearDist, origin.z + axis.m_z * nearDist));
				LEVector3 nearnorm = LEVector3((nearPlane.getPoint().x - origin.x), (nearPlane.getPoint().y - origin.y), (nearPlane.getPoint().z - origin.z));
				nearnorm.Normalize();
				nearPlane.setNormal(nearnorm);
				//far plane
				farPlane.setPoint(PrimitiveShapes::Point(origin.x + axis.m_x * farDist, origin.y + axis.m_y * farDist, origin.z + axis.m_z * farDist));
				LEVector3 farnorm = LEVector3(nearnorm);
				//farnorm -= farnorm;

				farPlane.setNormal(-farnorm);

				Primitives::Float32 tantheta = tanf(theta);
				Primitives::Float32 halfhightnear = tantheta * nearDist;
				Primitives::Float32 halfheightfar = tantheta * farDist;

				PrimitiveShapes::Point A, B, C, D, E, F, G, H;
				//near plane points.
				LEVector3 right = LEVector3();
				right.crossProduct(axis, up);

				A = PrimitiveShapes::Point(halfhightnear*(-up - right) + nearDist*axis);
				B = PrimitiveShapes::Point(halfhightnear*(up - right) + nearDist*axis);
				C = PrimitiveShapes::Point(halfhightnear*(up + right) + nearDist*axis);
				D = PrimitiveShapes::Point(halfhightnear*(-up + right) + nearDist*axis);
				//far plane points.

				H = PrimitiveShapes::Point(halfheightfar*(-up - right) + farDist*axis);
				G = PrimitiveShapes::Point(halfheightfar*(up - right) + farDist*axis);
				F = PrimitiveShapes::Point(halfheightfar*(up + right) + farDist*axis);
				E = PrimitiveShapes::Point(halfheightfar*(-up + right) + farDist*axis);

				//topPlane plane
				topPlane.setPoint(PrimitiveShapes::Point(nearPlane.getPoint().x, nearPlane.getPoint().y + halfhightnear, nearPlane.getPoint().z));
				topPlane.setNormal((normalGivenPoints(C, B, G)));
				//Bottom plane
				bottomPlane.setPoint(PrimitiveShapes::Point(nearPlane.getPoint().x, nearPlane.getPoint().y - halfhightnear, nearPlane.getPoint().z));
				bottomPlane.setNormal((normalGivenPoints(E, H, A)));
				//left plane.
				leftPlane.setPoint(PrimitiveShapes::Point(nearPlane.getPoint().x - halfhightnear, nearPlane.getPoint().y, nearPlane.getPoint().z));
				leftPlane.setNormal((normalGivenPoints(E, D, C)));
				//right plane.
				rightPlane.setPoint(PrimitiveShapes::Point(nearPlane.getPoint().x + halfhightnear, nearPlane.getPoint().y, nearPlane.getPoint().z));
				rightPlane.setNormal((normalGivenPoints(A, H, G)));


			}
			//eight world space points in counter clockwise order
			Frustrum(PrimitiveShapes::Point A, PrimitiveShapes::Point B,
				PrimitiveShapes::Point C, PrimitiveShapes::Point D,
				PrimitiveShapes::Point E, PrimitiveShapes::Point F,
				PrimitiveShapes::Point G, PrimitiveShapes::Point H,ColliderMeta meta) : Collider(meta) {
				setColliderType(ColliderType::TypeFrustrum);
				//near plane

				nearPlane.setPoint(A);
				nearPlane.setNormal((normalGivenPoints(A, B, C)));
				//top plane
				topPlane.setPoint(B);
				topPlane.setNormal((normalGivenPoints(C, B, G)));
				//Bottom plane
				bottomPlane.setPoint(A);
				bottomPlane.setNormal((normalGivenPoints(E, H, A)));
				//left plane.
				leftPlane.setPoint(C);
				leftPlane.setNormal((normalGivenPoints(E, D, C)));
				//right plane.
				rightPlane.setPoint(A);
				rightPlane.setNormal((normalGivenPoints(A, H, G)));
				//far plane.
				farPlane.setPoint(G);
				farPlane.setNormal((normalGivenPoints(F, G, H)));


			}
			//Points are counterclockwise (Left hand system).
			LEVector3 normalGivenPoints(PrimitiveShapes::Point A,
				PrimitiveShapes::Point B, PrimitiveShapes::Point C) {
				LEVector3 v1 = LEVector3(B.x - A.x, B.y - A.y, B.z - A.z);
				LEVector3 v2 = LEVector3(C.x - B.x, C.y - B.y, C.z - B.z);
				v1.Normalize();
				v2.Normalize();
				v1.crossProduct(v2);
				return v1;
			}
			
			PrimitiveShapes::Point getFurthestInDir(LEVector3 *Dir) override {
				LEVector3 localDir = *Dir * getMetaData().objMat;
				localDir.Normalize();

				PrimitiveShapes::Point center = PrimitiveShapes::Point(farPlane.getPoint().x - nearPlane.getPoint().x,
					farPlane.getPoint().y - nearPlane.getPoint().y,
					farPlane.getPoint().z - nearPlane.getPoint().z);
				
				for (unsigned int i = 0; i < 6; i++) {
					
				}
				return PrimitiveShapes::Point();


			}
			void generateValuesFromBuffer(vector<Primitives::Float32> vertices){}
			Frustrum(Frustrum const&) {}

		};
		
		
		
		
	
		

	};
};

#endif // !FRUSTRUM_H_

