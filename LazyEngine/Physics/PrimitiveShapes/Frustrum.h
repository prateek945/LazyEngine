#pragma once
#ifndef FRUSTRUM_H_
#define FRUSTRUM_H_
#include "../../Includes//LazyIncludes.h"
#include "Plane.h"
#include "Point.h"
namespace LE {
	namespace PrimitiveShapes {
		template <class T = Primitives::Float32>
		class Frustrum {

			Plane<T> nearPlane, farPlane, leftPlane, rightPlane, topPlane, bottomPlane;

		public:
			//NOTE : Plane normales are defined to be inwards for all 6 planes.
			//NOTE : Z Axis is forward axis WOrld space or otherwise.

			//Generating planes from FOV (in degrees), origin, near and far clip distances.
			Frustrum() {}
			Frustrum( Point<T> origin,  LEVector3<T> ForwardAxis, LEVector3<T> UpAxis, const Primitives::Float32 FOV, const Primitives::Float32 nearDist, const Primitives::Float32 farDist);
			//eight world space points in counter clockwise order
			Frustrum(Point<T> A, Point<T> B, Point<T> C, Point<T> D, Point<T> E, Point<T> F, Point<T> G, Point<T> H);
			//Points are counterclockwise (Left hand system).
			LEVector3<T> normalGivenPoints(Point<T> A, Point<T> B, Point<T> C);

		};
		template<class T>
		Frustrum<T>::Frustrum(Point<T> origin, LEVector3<T> axis, LEVector3<T> up,const Primitives::Float32 FOV, const Primitives::Float32 nearDist, const Primitives::Float32 farDist) {
			//Setup Near and Far clip planes first.
			Primitives::Float32 theta = DEGTORAD(FOV) / 2.f;
			//near plane
			axis.Normalize();
			up.Normalize();
			nearPlane.setPoint(Point<T>(origin.x + axis.m_x * nearDist, origin.y + axis.m_y * nearDist, origin.z + axis.m_z * nearDist));
			LEVector3<T> nearnorm = LEVector3<T>((nearPlane.getPoint().x - origin.x), (nearPlane.getPoint().y - origin.y), (nearPlane.getPoint().z - origin.z));
			nearnorm.Normalize();
			nearPlane.setNormal(nearnorm);
			//far plane
			farPlane.setPoint(Point<T>(origin.x + axis.m_x * farDist, origin.y + axis.m_y * farDist, origin.z + axis.m_z * farDist));
			LEVector3<T> farnorm = LEVector3<T>(nearnorm);
			//farnorm -= farnorm;
			
			farPlane.setNormal(-farnorm);
			
			Primitives::Float32 tantheta = tanf(theta);
			Primitives::Float32 halfhightnear = tantheta * nearDist;
			Primitives::Float32 halfheightfar = tantheta * farDist;

			Point<T> A, B, C, D, E, F, G, H;
			//near plane points.
			LEVector3<T> right = LEVector3<T>();
			right.crossProduct(axis, up);

			A = Point<T>(halfhightnear*(-up - right)+nearDist*axis);
			B = Point<T>(halfhightnear*(up - right) + nearDist*axis);
			C = Point<T>(halfhightnear*(up + right) + nearDist*axis);
			D = Point<T>(halfhightnear*(-up + right) + nearDist*axis);
			//far plane points.

			H = Point<T>(halfheightfar*(-up - right) + farDist*axis);
			G = Point<T>(halfheightfar*(up - right) + farDist*axis);
			F = Point<T>(halfheightfar*(up + right) + farDist*axis);
			E = Point<T>(halfheightfar*(-up + right) + farDist*axis);

			//topPlane plane
			topPlane.setPoint(Point<T>(nearPlane.getPoint().x, nearPlane.getPoint().y + halfhightnear, nearPlane.getPoint().z));
			topPlane.setNormal((normalGivenPoints(C, B, G)));
			//Bottom plane
			bottomPlane.setPoint(Point<T>(nearPlane.getPoint().x, nearPlane.getPoint().y - halfhightnear, nearPlane.getPoint().z));
			bottomPlane.setNormal((normalGivenPoints(E, H, A)));
			//left plane.
			leftPlane.setPoint(Point<T>(nearPlane.getPoint().x - halfhightnear, nearPlane.getPoint().y, nearPlane.getPoint().z));
			leftPlane.setNormal((normalGivenPoints(E, D, C)));
			//right plane.
			rightPlane.setPoint(Point<T>(nearPlane.getPoint().x + halfhightnear, nearPlane.getPoint().y, nearPlane.getPoint().z));
			rightPlane.setNormal((normalGivenPoints(A, H, G)));
		}

		template <class T>
		Frustrum<T>::Frustrum<T>(Point<T> A, Point<T> B, Point<T> C, Point<T> D, Point<T> E, Point<T> F, Point<T> G, Point<T> H) {
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

		template <class T>
		LEVector3<T> Frustrum<T>::normalGivenPoints(Point<T> A, Point<T> B, Point<T> C) {
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

