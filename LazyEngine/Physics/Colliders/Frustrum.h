#pragma once
#ifndef FRUSTRUM_H_
#define FRUSTRUM_H_
#include "../../Includes/LazyIncludes.h"
#include "ColliderMeta.h"
#include "../PrimitiveShapes/Plane.h"
#include "../PrimitiveShapes/Point.h"
namespace LE {
	namespace Colliders {
		template <class T = Primitives::Float32>
		class Frustrum {
			ColliderMeta metaData;
			PrimitiveShapes::Plane<T> nearPlane, farPlane, leftPlane, rightPlane, topPlane, bottomPlane;

		public:
			//NOTE : Plane normales are defined to be inwards for all 6 planes.
			//NOTE : Z Axis is forward axis WOrld space or otherwise.

			//Generating planes from FOV (in degrees), origin, near and far clip distances.
			Frustrum() {}
			Frustrum(PrimitiveShapes::Point<T> origin, LEVector3<T> ForwardAxis, LEVector3<T> UpAxis, const Primitives::Float32 FOV, const Primitives::Float32 nearDist, const Primitives::Float32 farDist);
			//eight world space points in counter clockwise order
			Frustrum(PrimitiveShapes::Point<T> A, PrimitiveShapes::Point<T> B, 
				PrimitiveShapes::Point<T> C, PrimitiveShapes::Point<T> D, 
				PrimitiveShapes::Point<T> E, PrimitiveShapes::Point<T> F, 
				PrimitiveShapes::Point<T> G, PrimitiveShapes::Point<T> H);
			//Points are counterclockwise (Left hand system).
			LEVector3<T> normalGivenPoints(PrimitiveShapes::Point<T> A, 
				PrimitiveShapes::Point<T> B, PrimitiveShapes::Point<T> C);

			ColliderMeta getMetaData() {
				return metaData;
			}

		};
		template<class T>
		Frustrum<T>::Frustrum(PrimitiveShapes::Point<T> origin, LEVector3<T> axis, LEVector3<T> up, const Primitives::Float32 FOV, const Primitives::Float32 nearDist, const Primitives::Float32 farDist) {
			//Setup Near and Far clip planes first.
			Primitives::Float32 theta = DEGTORAD(FOV) / 2.f;
			//near plane
			axis.Normalize();
			up.Normalize();
			nearPlane.setPoint(PrimitiveShapes::Point<T>(origin.x + axis.m_x * nearDist, origin.y + axis.m_y * nearDist, origin.z + axis.m_z * nearDist));
			LEVector3<T> nearnorm = LEVector3<T>((nearPlane.getPoint().x - origin.x), (nearPlane.getPoint().y - origin.y), (nearPlane.getPoint().z - origin.z));
			nearnorm.Normalize();
			nearPlane.setNormal(nearnorm);
			//far plane
			farPlane.setPoint(PrimitiveShapes::Point<T>(origin.x + axis.m_x * farDist, origin.y + axis.m_y * farDist, origin.z + axis.m_z * farDist));
			LEVector3<T> farnorm = LEVector3<T>(nearnorm);
			//farnorm -= farnorm;

			farPlane.setNormal(-farnorm);

			Primitives::Float32 tantheta = tanf(theta);
			Primitives::Float32 halfhightnear = tantheta * nearDist;
			Primitives::Float32 halfheightfar = tantheta * farDist;

			PrimitiveShapes::Point<T> A, B, C, D, E, F, G, H;
			//near plane points.
			LEVector3<T> right = LEVector3<T>();
			right.crossProduct(axis, up);

			A = PrimitiveShapes::Point<T>(halfhightnear*(-up - right) + nearDist*axis);
			B = PrimitiveShapes::Point<T>(halfhightnear*(up - right) + nearDist*axis);
			C = PrimitiveShapes::Point<T>(halfhightnear*(up + right) + nearDist*axis);
			D = PrimitiveShapes::Point<T>(halfhightnear*(-up + right) + nearDist*axis);
			//far plane points.

			H = PrimitiveShapes::Point<T>(halfheightfar*(-up - right) + farDist*axis);
			G = PrimitiveShapes::Point<T>(halfheightfar*(up - right) + farDist*axis);
			F = PrimitiveShapes::Point<T>(halfheightfar*(up + right) + farDist*axis);
			E = PrimitiveShapes::Point<T>(halfheightfar*(-up + right) + farDist*axis);

			//topPlane plane
			topPlane.setPoint(PrimitiveShapes::Point<T>(nearPlane.getPoint().x, nearPlane.getPoint().y + halfhightnear, nearPlane.getPoint().z));
			topPlane.setNormal((normalGivenPoints(C, B, G)));
			//Bottom plane
			bottomPlane.setPoint(PrimitiveShapes::Point<T>(nearPlane.getPoint().x, nearPlane.getPoint().y - halfhightnear, nearPlane.getPoint().z));
			bottomPlane.setNormal((normalGivenPoints(E, H, A)));
			//left plane.
			leftPlane.setPoint(PrimitiveShapes::Point<T>(nearPlane.getPoint().x - halfhightnear, nearPlane.getPoint().y, nearPlane.getPoint().z));
			leftPlane.setNormal((normalGivenPoints(E, D, C)));
			//right plane.
			rightPlane.setPoint(PrimitiveShapes::Point<T>(nearPlane.getPoint().x + halfhightnear, nearPlane.getPoint().y, nearPlane.getPoint().z));
			rightPlane.setNormal((normalGivenPoints(A, H, G)));

			this->metaData.type = ColliderType::Frustrum;
		}

		template <class T>
		Frustrum<T>::Frustrum<T>(PrimitiveShapes::Point<T> A, PrimitiveShapes::Point<T> B,
			PrimitiveShapes::Point<T> C, PrimitiveShapes::Point<T> D,
			PrimitiveShapes::Point<T> E, PrimitiveShapes::Point<T> F,
			PrimitiveShapes::Point<T> G, PrimitiveShapes::Point<T> H) {
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
			this->metaData.type = ColliderType::Frustrum;
		}

		template <class T>
		LEVector3<T> Frustrum<T>::normalGivenPoints(PrimitiveShapes::Point<T> A,
			PrimitiveShapes::Point<T> B, PrimitiveShapes::Point<T> C) {
			LEVector3<T> v1 = LEVector3<T>(B.x - A.x, B.y - A.y, B.z - A.z);
			LEVector3<T> v2 = LEVector3<T>(C.x - B.x, C.y - B.y, C.z - B.z);
			v1.Normalize();
			v2.Normalize();
			v1.crossProduct(v2);
			return v1;
		}
	};
};

#endif // !FRUSTRUM_H_

